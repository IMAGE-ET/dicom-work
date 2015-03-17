#ifndef __PTT_UART_H__
#define __PTT_UART_H__
#include <pjlib.h>
void pttc_init( void (*cb)(int) );
void pttc_start( pj_pool_t *pool, char *port_dev, pj_thread_t **thread );
void pttc_end( pj_thread_t *thread );
#endif
