#include "pttc_uart.h"
#include "serial_utils.h"

void on_pttc_data_received(char *buffer, int nbytes);
void pttc_process_command(int fd) { /* DO NOTHING. PTT card has no controling command */ }

/* Parser for PTT Card control */
struct {
    int f_complete;
    int f_on;
} pttc_parser;

inline void pttc_parser_set_complete() {
    pttc_parser.f_complete = 1;
}
inline void pttc_parser_set_incomplete() {
    pttc_parser.f_complete = 0;
}
inline int pttc_parser_is_complete() {
    return pttc_parser.f_complete == 1;
}
inline void pttc_parser_set_on() {
    pttc_parser.f_on = 1;
}
inline void pttc_parser_set_off() {
    pttc_parser.f_on = 0;
}
inline int pttc_parser_is_on() {
    return pttc_parser.f_on == 1;
}

void (*on_pttc_ptt)(int ptt);

void on_pttc_ptt_default(int ptt) {
    PJ_LOG(3, (__FILE__, "PTT is %d", ptt));
}

void pttc_init( void (*cb)(int) ) {
    on_serial_data_received = on_pttc_data_received;
    process_command = pttc_process_command;
    if( cb != 0) 
        on_pttc_ptt = cb;
    else 
        on_pttc_ptt = on_pttc_ptt_default;
}

void pttc_start( pj_pool_t *pool, char *port_dev, pj_thread_t **thread ) {
    serial_start(pool, port_dev, thread);
}

void pttc_end( pj_thread_t *thread ) {
    serial_end(thread);
}

void on_pttc_data_received(char *buffer, int nbytes) {
    int i;
    for( i = 0; i < nbytes; i++ ) {
        switch (buffer[i]) {
        case 'L':
            pttc_parser_set_incomplete();
            break;
        case '0':
            pttc_parser_set_complete();
            pttc_parser_set_off();
            break;
        case '1':
            pttc_parser_set_complete();
            pttc_parser_set_on();
            break;
        default:
            PJ_LOG(3, (__FILE__, "invalid parsed input: %c (%d)\n", buffer[i], buffer[i]));
            break;
        }
        if( pttc_parser_is_complete() ) {
            on_pttc_ptt(pttc_parser_is_on());
        }
    }
}

