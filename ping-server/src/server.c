#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "udp-server.h"
#include "duplex-socket.h"
void clone_data(dupsock_in_packet_t *in_packet, dupsock_out_packet_t *out_packet) {
    pj_memcpy(out_packet->data, in_packet->data, in_packet->len);
    out_packet->len = in_packet->len;
    out_packet->sent = 0;
}

int main() {
    pj_caching_pool cp;
    pj_pool_t *pool;
    udpserver_t udps;

    pj_log_set_level(3);
    CHECK(__FILE__, pj_init());
    pj_caching_pool_init(&cp, NULL, 1*128);
    pool = pj_pool_create(&cp.factory, "server", 128, 128, NULL);

    udps_init(&udps, 33333, pool, &clone_data);
    udps_start(&udps);
    
//    pj_thread_sleep(30 * 1000);
//    while (1) {
//        pj_thread_sleep(30 * 1000);
//    }
    pj_thread_join(udps.snd_thread);

    udps_end(&udps);
    pj_pool_release(pool);
    pj_caching_pool_destroy(&cp);

    pj_shutdown();
    return 0;
}
