#include <pjlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include "my-pjlib-utils.h"
/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff);
}

int main() {
    pj_sock_t sock;
    pj_sockaddr_in to_addr;
    char *s = "Cong hoa xa hoi chu nghia VietNam";

    char buffer[100];
    pj_ssize_t len;

    struct timeval tv_begin, tv_end, tv_diff;

    pj_log_set_level(4);
    CHECK(__FILE__, pj_init());
    pj_bzero(buffer, sizeof(buffer));
    CHECK_R( __FILE__, pj_sock_socket(PJ_AF_INET, PJ_SOCK_DGRAM, 0, &sock) );
    //udp_socket(12345, &sock);
    setup_addr_with_host_and_port(&to_addr, "127.0.0.1", 33333);

    len = strlen(s);
    gettimeofday(&tv_begin, NULL);
    pj_sock_sendto(sock, s, &len, 0, &to_addr, sizeof(to_addr));
    
    PJ_LOG(3, (__FILE__, "Sent: %s", s));
    len = 100;
    pj_sock_recv(sock, buffer, &len, 0);
    gettimeofday(&tv_end, NULL);
    int diff = timeval_subtract(&tv_diff, &tv_end, &tv_begin);
    PJ_LOG(3, (__FILE__, "Received: %s %0.2f msec", buffer, diff*1.0/1000));
    pj_shutdown();
    return 0;
}
