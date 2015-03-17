#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "udp-server.h"
#include "duplex-socket.h"
//#include "arbiter.h"

void process_data(dupsock_in_packet_t *in_packet, dupsock_out_packet_t *out_packet) {
}

int main() {
    pj_caching_pool cp;
    pj_pool_t *pool;

    udpserver_t udps;
    int port = 33333;

    pj_log_set_level(4);
    CHECK(__FILE__, pj_init());
    pj_caching_pool_init(&cp, NULL, 1*128);
    pj_pool_create(&cp.factory, "arbiter", 128, 128, NULL);

    
    udps_init(&udps, 33333, pool, &process_data);
    udps_start(&udps);

    pj_shutdown();
    return 0;
}
