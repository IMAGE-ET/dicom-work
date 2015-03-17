#include "dicom-config.h"
#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "duplex-socket.h"
#define CONFIG_FILE "../conf/config.ini"

static int on_data_received(dupsock_t *p_dupsock) {
    return 0;
}

static int on_data_sent(dupsock_t *p_dupsock) {
    return 0;
}

void call_sip(const char *sip_uri) {

}

void call_ptt(pj_sockaddr_in ptt_addr) {
    // seige arbiter if ptt now is ok, seiging is successful

    // 
}

void 

int main() {
    dicom_config_t config;

    pj_caching_pool cp;
    pj_pool_t *pool;

    pj_sock_t sock;
    pj_sockaddr_in ptt_addr;
    dupsock_t dupsock;


    pj_log_set_level(4);
    CHECK(__FILE__, pj_init());

    pj_caching_pool_init(&cp, NULL, 1*1024);
    pool = pj_pool_create(&cp.factory, "simple-oiu", 128, 128, NULL);

    CHECK_NULL(__FILE__, pool);

    dicom_config_load( CONFIG_FILE, &config );

    setup_addr_with_host_and_port(&ptt_addr, config.ptt_group.ipmaddr, config.ptt_group.port);

    CHECK( __FILE__, udp_socket(config.ptt_group.port, &sock) );
    CHECK( __FILE__, join_mcast_group( sock, config.ptt_group.ipmaddr) );

    dupsock_init(&dupsock, &sock, pool, &on_data_received, &on_data_sent);
    dupsock_start(&dupsock);

    dupsock_end(&dupsock);

    return 0;
}

