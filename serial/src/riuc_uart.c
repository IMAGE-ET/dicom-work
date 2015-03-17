#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
//#include <termios.h>
#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "serial_utils.h"

volatile int onPTT;
volatile int offPTT;

volatile int fLED;
volatile int fSQ;

typedef struct _uart_status_t {
    int ptt;
    int sq;
} uart_status_t;

uart_status_t uart_status;

struct {
    int l0s1; // ptt or sq
    int f_complete; // complete or not
    int f_on; // on or off
} parser;

void (*on_riuc_status)(void *data);
void (*on_riuc_error)(int error_code);

inline int parser_is_ptt() {
    return parser.l0s1 == 0;
}
inline int parser_is_complete() {
    return parser.f_complete;
}
inline int parser_is_on() {
    return parser.f_on;
}
inline void parser_set_ptt() {
    parser.l0s1 = 0;
}
inline void parser_set_sq() {
    parser.l0s1 = 1;
}
inline void parser_set_complete() {
    parser.f_complete = 1;
}

inline void parser_set_incomplete() {
    parser.f_complete = 0;
}

inline void parser_set_on() {
    parser.f_on = 1;
}

inline void parser_set_off() {
    parser.f_on = 0;
}

void on_riuc_status_default(void *data) {
    uart_status_t *ustatus = (uart_status_t *)data;
    PJ_LOG(3, ("RIUC", "ptt:%d - sq:%d", ustatus->ptt, ustatus->sq));
}

void on_riuc_data_received_default(char *buffer, int nbytes) {
    int i;
    for( i = 0; i < nbytes; i++ ) {
        switch (buffer[i]) {
        case 'L':
            parser_set_ptt();
            parser_set_incomplete();
            break;
        case 'Q':
            parser_set_sq();
            parser_set_incomplete();
            break;
        case '0':
            parser_set_complete();
            parser_set_off();
            break;
        case '1':
            parser_set_complete();
            parser_set_on();
            break;
        default:
            PJ_LOG(3, (__FILE__, "invalid parsed input: %c (%d)\n", buffer[i], buffer[i]));
            break;
        }
        if( parser_is_complete() ) {
            if( parser_is_ptt() ) {
                uart_status.ptt = parser_is_on();
            }
            else {
                uart_status.sq = parser_is_on();
            }
            on_riuc_status(&uart_status);
        }
    }
}

void on_ptt(int fd) {
    int nbytes;
    PJ_LOG(3, (__FILE__, "on_ptt()"));
    nbytes = write(fd, "onptt\r", 6);
}
void off_ptt(int fd) {
    int nbytes;
    PJ_LOG(3, (__FILE__, "off_ptt()"));
    nbytes = write(fd, "offptt\r", 7);
}

void probLED(int fd) {
    int nbytes;
    nbytes = write(fd, "chkled\r", 7);
}

void probSQ(int fd) {
    int nbytes;
    nbytes = write(fd, "chksq\r", 6);
}

void riuc_process_command(int fd) {
    if (fLED) {
        fLED = 0;
        probLED(fd);
    }
    if (fSQ) {
        fSQ = 0;
        probSQ(fd);
    }
    if (onPTT) {
        onPTT = 0;
        on_ptt(fd);
    }
    if (offPTT) {
        offPTT = 0;
        off_ptt(fd);
    }
}

void riuc_init(void (*cb)(void *)) {
    on_serial_data_received = on_riuc_data_received_default;
    process_command = riuc_process_command;

    if( cb == NULL ) 
        on_riuc_status = on_riuc_status_default;
    else 
        on_riuc_status = cb;
}

void riuc_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread) {
    fLED = 0;
    fSQ = 0;
    serial_start(pool, port_dev, thread);
}

void riuc_end(pj_thread_t *thread) {
    serial_end(thread);
}

void riuc_probe_sq() {
    fSQ = 1;
}

void riuc_probe_ptt() {
    fLED = 1;
}

void riuc_on_ptt() {
    PJ_LOG(3, (__FILE__, "riuc_on_ptt()"));
    onPTT = 1;
}

void riuc_off_ptt() {
    PJ_LOG(3, (__FILE__, "riuc_off_ptt()"));
    offPTT = 1;
}

