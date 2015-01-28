#ifndef __DUPLEX_SOCKET__
#define __DUPLEX_SOCKET__

#include <pjlib.h>

#define DUPSOCK_IN_BUFSIZE 500
typedef struct dupsock_s dupsock_t;
typedef int (*dupsock_callback_proc)(dupsock_t *p_dupsock);

typedef struct {
    pj_sockaddr_in addr;
    char *data;
    int len;
    int sent;
    void *p_user;
} dupsock_out_packet_t;

typedef struct {
    pj_sockaddr_in addr;
    char *data;
    int len;
    void *user;
} dupsock_in_packet_t;

struct dupsock_s{
    pj_sock_t *p_sock;
    pj_pool_t *p_mempool;
    volatile int b_quit;
    pj_thread_t *thread;

    volatile dupsock_out_packet_t *to_send;
    dupsock_in_packet_t in_packet;
    
    volatile int wait_cnt;

    void *p_user;
    // INTERNAL USE
    pj_fd_set_t rfds;
    pj_fd_set_t wfds;

    dupsock_callback_proc recv_callback;
    dupsock_callback_proc send_callback;

    char in_buffer[DUPSOCK_IN_BUFSIZE];
    
    pj_event_t *p_event;
};

void dupsock_init(dupsock_t *p_dupsock, pj_sock_t *p_sock, pj_pool_t *p_mempool, dupsock_callback_proc rcb, dupsock_callback_proc scb);
void dupsock_start(dupsock_t *p_dupsock);
int dupsock_send(dupsock_t *p_dupsock, dupsock_out_packet_t *packet);
void dupsock_end(dupsock_t *p_dupsock);
#endif
