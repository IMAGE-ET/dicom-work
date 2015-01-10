#include "my-pjlib-utils.h"

pj_status_t __mpu_status;
void err(const char *__file, const char *op, pj_status_t status) {
	char errmsg[PJ_ERR_MSG_SIZE];
	pj_strerror(status, errmsg, sizeof(errmsg));
	PJ_LOG(3, (__file, "%s error: %s", op, errmsg));
}

void setup_addr_with_port(pj_sockaddr_in *paddr, int port) {
	pj_bzero(paddr, sizeof(pj_sockaddr_in));
	paddr->sin_family = PJ_AF_INET;
	paddr->sin_port = pj_htons(port);
}

void setup_addr_with_host_and_port(pj_sockaddr_in *paddr, const char *host, int port) {
	pj_str_t s;
	pj_bzero(paddr, sizeof(pj_sockaddr_in));
	paddr->sin_family = PJ_AF_INET;
	paddr->sin_port = pj_htons(port);
	paddr->sin_addr = pj_inet_addr(pj_cstr(&s, host));
}

pj_status_t setup_udp_socket(int lport, pj_sock_t *sock, pj_sockaddr_in *paddr) {
	CHECK_R( __FILE__, pj_sock_socket(PJ_AF_INET, PJ_SOCK_DGRAM, 0, sock) );
    setup_addr_with_port(paddr, lport);
	CHECK_R( __FILE__, pj_sock_bind(*sock, paddr, sizeof(pj_sockaddr_in)) );
    return PJ_SUCCESS;
}

pj_status_t join_mcast_group(pj_sock_t sock, const char* mcast) {
	pj_ip_mreq mreq;
    pj_str_t s, s1;

	pj_bzero(&mreq, sizeof(pj_ip_mreq));
	mreq.imr_multiaddr = pj_inet_addr(pj_cstr(&s, mcast));
	mreq.imr_interface = pj_inet_addr(pj_cstr(&s1, "0.0.0.0"));

	CHECK( __FILE__, pj_sock_setsockopt(sock, PJ_SOL_IP, PJ_IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) );

    return PJ_SUCCESS;
}

