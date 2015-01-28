#include "my-pjlib-utils.h"
#include "duplex-socket.h"
#include <pjlib.h>
/*#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>*/

void dupsock_init(dupsock_t *p_dupsock, pj_sock_t *p_sock, pj_pool_t *p_mempool, 
                  dupsock_callback_proc rcb, dupsock_callback_proc scb) 
{
    p_dupsock->p_sock = p_sock;
    p_dupsock->p_mempool = p_mempool;
    p_dupsock->thread = NULL;

    p_dupsock->recv_callback = rcb;
    p_dupsock->send_callback = scb;
    
    p_dupsock->to_send = NULL;
    p_dupsock->in_packet.data = p_dupsock->in_buffer;
    p_dupsock->in_packet.len = 0;

    pj_event_create(p_dupsock->p_mempool, "dupsock-event", PJ_FALSE, PJ_TRUE, &(p_dupsock->p_event));
    pj_event_reset(p_dupsock->p_event);
    p_dupsock->wait_cnt = 0;
    p_dupsock->p_user = NULL;
}

static int thread_proc(void *data) {
    dupsock_t *p_dupsock = (dupsock_t *)data;
    pj_thread_t *thread;
    pj_thread_desc desc;
    struct pj_time_val tv;
    int ret;
    pj_ssize_t ntemp;
    int sock_len;
    
//    pj_bzero(desc, sizeof(desc));
//    CHECK(__FILE__, pj_thread_register("dupsock", desc, &thread));

    PJ_FD_ZERO(&(p_dupsock->rfds));
    PJ_FD_ZERO(&(p_dupsock->wfds));

    PJ_FD_SET(*(p_dupsock->p_sock), &(p_dupsock->rfds));

    tv.sec = 0;
    tv.msec = 20;
    // MAIN LOOP
    p_dupsock->b_quit = 0;
    while( (!p_dupsock->b_quit) || (p_dupsock->wait_cnt > 0) || (p_dupsock->to_send != NULL) ) {
        if(p_dupsock->wait_cnt > 0) {
            p_dupsock->wait_cnt--;
            pj_event_pulse(p_dupsock->p_event);
        }

        pj_thread_sleep(10);

        PJ_FD_ZERO(&(p_dupsock->rfds));
        PJ_FD_ZERO(&(p_dupsock->wfds));

        PJ_FD_SET(*(p_dupsock->p_sock), &(p_dupsock->rfds));
        if(p_dupsock->to_send != NULL) 
            PJ_FD_SET(*(p_dupsock->p_sock), &(p_dupsock->wfds));

        ret = pj_sock_select(*(p_dupsock->p_sock) + 1, &(p_dupsock->rfds), &(p_dupsock->wfds), NULL, &tv);
        if( ret < 0 ) {
            PJ_LOG(2, (__FILE__, "Error in select"));
        }
        else if (ret > 0) {
            if( PJ_FD_ISSET( *(p_dupsock->p_sock), &(p_dupsock->rfds)) ){
                ntemp = sizeof(p_dupsock->in_buffer);
                sock_len = sizeof(p_dupsock->in_packet.addr);
                pj_sock_recvfrom(*(p_dupsock->p_sock), p_dupsock->in_packet.data, &ntemp, 0, (pj_sockaddr_t *)(&(p_dupsock->in_packet.addr)), &sock_len);
                p_dupsock->in_packet.len = ntemp;
                if(p_dupsock->recv_callback != NULL) {
                    p_dupsock->recv_callback(p_dupsock);
                }
                p_dupsock->in_packet.len = 0;
            }
            if( PJ_FD_ISSET( *(p_dupsock->p_sock), &(p_dupsock->wfds)) ) {
                ntemp = p_dupsock->to_send->len - p_dupsock->to_send->sent;
                pj_sock_sendto(*(p_dupsock->p_sock), 
                                p_dupsock->to_send->data + p_dupsock->to_send->sent, 
                                &ntemp, 0, (pj_sockaddr_t *)(&(p_dupsock->to_send->addr)), sizeof(p_dupsock->to_send->addr));
                p_dupsock->to_send->sent += ntemp;
                
                if(p_dupsock->to_send->len == p_dupsock->to_send->sent) {
                    if(p_dupsock->send_callback != NULL) {
                        p_dupsock->send_callback(p_dupsock);
                    }
                    p_dupsock->to_send = NULL;
                    PJ_FD_CLR(*(p_dupsock->p_sock), &(p_dupsock->wfds));
                }
            }
        }
        //PJ_LOG(5, (__FILE__, "end of a loop"));
    }
    pj_event_destroy(p_dupsock->p_event);
    pj_sock_close(*(p_dupsock->p_sock));
    return 0;
}

void dupsock_start(dupsock_t *p_dupsock) {
    pj_thread_create(p_dupsock->p_mempool, "dupsock", 
                     &thread_proc, p_dupsock, PJ_THREAD_DEFAULT_STACK_SIZE, 
                     0, &(p_dupsock->thread));
}

int dupsock_send(dupsock_t *p_dupsock, dupsock_out_packet_t *packet) {
    p_dupsock->wait_cnt++;
    pj_event_wait(p_dupsock->p_event);
    p_dupsock->to_send = packet;
    packet->sent = 0;
    return 0;
}

void dupsock_end(dupsock_t *p_dupsock) {
    PJ_LOG(5, (__FILE__, "Ending dupsock"));
    p_dupsock->b_quit = 1;
    pj_thread_join(p_dupsock->thread);
}
