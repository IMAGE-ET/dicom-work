#ifndef __MY_PJLIB_UTILS_H__
#define __MY_PJLIB_UTILS_H__

#include <pjlib.h>

void err(const char *__file, const char *op, pj_status_t status);

void setup_addr_with_port(pj_sockaddr_in *paddr, int port);
void setup_addr_with_host_and_port(pj_sockaddr_in *paddr, const char *host, int port);
pj_status_t setup_udp_socket(int lport, pj_sock_t *sock, pj_sockaddr_in *paddr);
pj_status_t udp_socket(int lport, pj_sock_t *sock);
pj_status_t join_mcast_group(pj_sock_t sock, const char* mcast);

extern pj_status_t __mpu_status;

#define CHECK(f, op) \
do { \
			__mpu_status = op; \
			if ( __mpu_status != PJ_SUCCESS ) { \
				err(f, #op, __mpu_status); \
				exit(-1); \
			} \
}  while(0)

#define CHECK_R(f, op) \
do { \
			__mpu_status = op; \
			if ( __mpu_status != PJ_SUCCESS ) { \
				err(f, #op, __mpu_status); \
				return __mpu_status; \
			} \
}  while(0)

#define CHECK_NULL(f, pointer) \
do { \
    if( pointer == NULL ) { \
        err(f, #pointer "is NULL", 0); \
        exit(-1); \
    } \
} while(0)

#define CHECK_NULL_R(f, pointer) \
do { \
    if( pointer == NULL ) { \
        err(f, #pointer "is NULL", 0); \
        return -1; \
    } \
} while(0)

#define CHECK_FALSE(f, bool_val) \
do { \
    if( !bool_val ) { \
        err(f, #bool_val "is FALSE", 0); \
        exit(-1); \
    } \
} while(0)

#define CHECK_FALSE_R(f, bool_val) \
do { \
    if( !bool_val ) { \
        err(f, #bool_val "is FALSE", 0); \
        return -1; \
    } \
} while(0)

#define PANIC(f, msg) \
do { \
    err(f, msg, 0); \
    exit(-1); \
} while(0)

#endif
