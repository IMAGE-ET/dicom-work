#include "udp-server.h"
#include "duplex-socket.h"
#include "my-pjlib-utils.h"
#include "queue.h"
#include <pjlib.h>

//#define UDPS_OUT_QEDATA(qe) (udps_out_event_data_t *)(qe->data)
#define UDPS_OUT_QEDATA(qe) (dupsock_out_packet_t *)(qe->data)

typedef struct udps_in_event_s {
    char data[DUPSOCK_IN_BUFSIZE];
    int len;
    pj_sockaddr_in addr;
} udps_in_event_data_t;

typedef struct udps_out_event_s {
    char data[DUPSOCK_IN_BUFSIZE];
    int len;
    pj_sockaddr_in addr;
} udps_out_event_data_t;

process_in_packet_proc process_in_packet;

/*
void udps_out_event_data_from_in_packet(udps_out_event_data_t *out_event, dupsock_in_packet_t *in_packet) {
    pj_memcpy(&(out_event->addr), &(in_packet->addr), sizeof(pj_sockaddr_in) );
    process_in_packet(in_packet, out_event);
}
*/
void dupsock_out_packet_from_in_packet(dupsock_out_packet_t *out_packet, dupsock_in_packet_t *in_packet) {
    pj_memcpy(&(out_packet->addr), &(in_packet->addr), sizeof(pj_sockaddr_in) );
    process_in_packet(in_packet, out_packet);
}

int on_data_received(dupsock_t *p_dupsock) {
    udpserver_t *p_udps = p_dupsock->p_user;

    queue_t *snd_queue = &(p_udps->snd_queue);
    queue_event_t *p_event = qepool_get(&(snd_queue->qepool));
    p_event->type = UDPS_SND_EVENT;

    dupsock_out_packet_t *out_packet = UDPS_OUT_QEDATA(p_event);
    opool_item_t *p_item = opool_get(&(p_udps->opool));
    out_packet->data = p_item->data;
    out_packet->p_user = p_event;
    p_event->p_user = p_item;
    out_packet->sent = 0;

    //udps_out_event_data_from_in_packet(out_event, &(p_dupsock->in_packet));
    dupsock_out_packet_from_in_packet(out_packet, &(p_dupsock->in_packet));

    queue_enqueue(snd_queue, p_event);
    return 1;
}

int on_data_sent(dupsock_t *p_dupsock) {
    udpserver_t *p_udps = (udpserver_t *)p_dupsock->p_user;
    volatile dupsock_out_packet_t *packet = p_dupsock->to_send;
    if( packet->sent >= packet->len ) {
        queue_event_t *p_event = (queue_event_t *)packet->p_user;
        opool_item_t *p_item = (opool_item_t *)p_event->p_user;
        opool_free(&(p_udps->opool), p_item);
        qepool_free(&(p_udps->snd_queue.qepool), p_event);
    }
    return 1;
}

static int rcv_thread_proc(void *data) {
    udpserver_t *p_udps = (udpserver_t *)data;
    queue_event_t *p_event;
    int b_quit = 0;
    while(!b_quit) {
        p_event = (queue_event_t *)queue_dequeue(&(p_udps->rcv_queue));
        switch (p_event->type) {
        case QE_EXIT:
            b_quit = 1;
            break;
        case UDPS_RCV_EVENT:
            break;
        default:
            break;
        }
    }
    return 0;
}


static int snd_thread_proc(void *data) {
    udpserver_t *p_udps = (udpserver_t *)data;
    queue_t *p_snd_queue = &(p_udps->snd_queue);
    queue_event_t *p_event;

    dupsock_out_packet_t out_packet;
    int b_quit = 0;
    while(!b_quit) {
        p_event = (queue_event_t *)queue_dequeue(p_snd_queue);
        switch (p_event->type) {
        case QE_EXIT:
            b_quit = 1;
            qepool_free(&(p_snd_queue->qepool), p_event);
            break;
        case UDPS_SND_EVENT:
            //dupsock_out_packet_from_udps_out_event_data(&out_packet, UDPS_OUT_QEDATA(p_event));
            //PJ_LOG(3, (__FILE__, "dupsock_send"));
            dupsock_send(&(p_udps->dupsock), UDPS_OUT_QEDATA(p_event));
            break;
        default:
            break;
        }
    }
    return 0;
}

void udps_init(udpserver_t *p_udps, int port, pj_pool_t *p_mempool, process_in_packet_proc f) {
    udp_socket(port, &(p_udps->sock));
    dupsock_init(&(p_udps->dupsock), &(p_udps->sock), p_mempool, &on_data_received, &on_data_sent);
    p_udps->dupsock.p_user = p_udps;
    p_udps->b_quit = 0;

    queue_init(&(p_udps->snd_queue),
               sizeof(p_udps->rcv_queue_buffer) / sizeof((p_udps->rcv_queue_buffer)[0]),
               sizeof(dupsock_out_packet_t), p_mempool);
    opool_init(&(p_udps->opool), 
               sizeof(p_udps->rcv_queue_buffer) / sizeof((p_udps->rcv_queue_buffer)[0]),
               DUPSOCK_IN_BUFSIZE, p_mempool);
    process_in_packet = f;
}

void udps_start(udpserver_t *p_udps) {
    dupsock_start(&(p_udps->dupsock));
    pj_thread_create(p_udps->dupsock.p_mempool, "udps-snd-thread", 
                     &snd_thread_proc, p_udps,
                     PJ_THREAD_DEFAULT_STACK_SIZE, 0,
                     &(p_udps->snd_thread));
}

void udps_end(udpserver_t *p_udps) {
    queue_t *snd_queue = &(p_udps->snd_queue);
    queue_event_t *p_event = qepool_get(&(snd_queue->qepool));
    p_event->type = QE_EXIT;

    queue_enqueue(snd_queue, p_event);
    pj_thread_join(p_udps->snd_thread);

    dupsock_end(&(p_udps->dupsock));
}
