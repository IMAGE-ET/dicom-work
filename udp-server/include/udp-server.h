#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__
#include <pjlib.h>
#include "duplex-socket.h"
#include "queue.h"
#include "object-pool.h"

#define UDPS_QUEUE_SIZE 100
// UDP Server events
enum {
    UDPS_RCV_EVENT = 2001,
    UDPS_SND_EVENT
};

typedef void (*process_in_packet_proc)(dupsock_in_packet_t *in_packet, dupsock_out_packet_t* out_packet);

typedef struct udpserver_s{
    pj_sock_t sock;
    dupsock_t dupsock;
    volatile int b_quit;

    pj_thread_t *snd_thread;
    pj_thread_t *rcv_thread;

    void *rcv_queue_buffer[UDPS_QUEUE_SIZE];
    void *snd_queue_buffer[UDPS_QUEUE_SIZE];
    queue_t rcv_queue;
    queue_t snd_queue;
    opool_t opool;
} udpserver_t;

void udps_init(udpserver_t *p_udps, int port, pj_pool_t *p_mempool, process_in_packet_proc f);
void udps_start(udpserver_t *p_udps);
void udps_end(udpserver_t *p_udps);
#endif
