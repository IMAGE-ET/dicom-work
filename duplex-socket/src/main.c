#include "my-pjlib-utils.h"
#include "duplex-socket.h"
#include <pjlib.h>
#include <stdlib.h>

int on_send_complete(dupsock_t *p_dupsock) {
    PJ_LOG(3, (__FILE__, "Sent: %.*s", p_dupsock->to_send->sent, p_dupsock->to_send->data));
    return 1;
}

int on_data_received(dupsock_t *p_dupsock) {
    PJ_LOG(3, (__FILE__, "Received: %.*s", p_dupsock->in_packet.len, p_dupsock->in_packet.data));
    return 1;
}
int main() {
    dupsock_t dupsock;
    pj_sock_t sock;
    pj_pool_t *p_mempool;
    pj_caching_pool cp;

    pj_log_set_level(4);
    CHECK(__FILE__, pj_init());

    pj_caching_pool_init(&cp, NULL, 1*1024);
    p_mempool = pj_pool_create(&cp.factory, "pool", 128, 128, NULL);

    CHECK(__FILE__, udp_socket(44444, &sock));
    CHECK(__FILE__, join_mcast_group(sock, "239.0.0.1"));
    dupsock_init(&dupsock, &sock, p_mempool, &on_data_received, &on_send_complete);
    dupsock_start(&dupsock);
    
    char *s1 = "Cong hoa xa hoi chu nghia Vietnam";
    char *s2 = "Doc lap tu do hanh phuc";

    dupsock_out_packet_t packet1, packet2;

    packet1.data = s1;
    packet1.len = strlen(s1);
    setup_addr_with_host_and_port(&(packet1.addr), "239.0.0.1", 44444);
    dupsock_send(&dupsock, &packet1);

    packet2.data = s2;
    packet2.len = strlen(s2);
    setup_addr_with_host_and_port(&(packet2.addr), "239.0.0.1", 44444);
    dupsock_send(&dupsock, &packet2);

    pj_thread_sleep(20); 
    dupsock_end(&dupsock);
    
    pj_pool_release(p_mempool);
    pj_caching_pool_destroy(&cp);

    pj_shutdown();
    return -1;
}
