#include "serial_utils.h"
#include "riuc_uart.h"

#define N_RIUC 4
#define RIUC_SIGNAL_PTT 1
#define RIUC_SIGNAL_SQ 2
#define RIUC_SIGNAL_ERROR 3
#define RIUC_SIGNAL_TX 4
#define RIUC_SIGNAL_RX 5

typedef struct _uart4_status_t {
    int ptt;
    int sq;
    int tx;
    int rx;
} uart4_status_t;

uart4_status_t riuc4_status[N_RIUC];
int riuc4_error;

struct {
    int signal; // 1=ptt(L) or 2=sq(Q) or 3=error(E) or 4=tx(T) or 5=rx(R). See define RIUC_SIGNAL_...
    int f_parsing_port; // parsing port or parsing value (1: parsing port)
    int f_complete; // complete or not
    int f_on; // on or off
    int port; // the port that output is saying about
} parser4;
void on_riuc4_status_default(void *data) {
    uart4_status_t *ustatus = (uart4_status_t *)data;
    PJ_LOG(3, ("RIUC4", "tx:%d - rx:%d - ptt:%d - sq:%d", ustatus->tx, ustatus->rx, ustatus->ptt, ustatus->sq));
}

void on_riuc4_error_default(int error_code) {
    PJ_LOG(3, ("RIUC4", "Error:%d", error_code));
}

void parser4_set_parsing_port() {
    parser4.f_parsing_port = 1;
}
void parser4_clear_parsing_port() {
    parser4.f_parsing_port = 0;
}
int parser4_is_parsing_port() {
    return parser4.f_parsing_port > 0;
}

void parser4_set_tx() {
    parser4.signal = RIUC_SIGNAL_TX;
}
void parser4_set_rx() {
    parser4.signal = RIUC_SIGNAL_RX;
}
void parser4_set_error() {
    parser4.signal = RIUC_SIGNAL_ERROR;
}
void parser4_set_ptt() {
    parser4.signal = RIUC_SIGNAL_PTT;
}
void parser4_set_sq() {
    parser4.signal = RIUC_SIGNAL_SQ;
}

int parser4_is_tx() {
    return parser4.signal == RIUC_SIGNAL_TX;
}
int parser4_is_rx() {
    return parser4.signal == RIUC_SIGNAL_RX;
}
int parser4_is_error() {
    return parser4.signal == RIUC_SIGNAL_ERROR;
}
int parser4_is_ptt() {
    return parser4.signal == RIUC_SIGNAL_PTT;
}
int parser4_is_sq() {
    return parser4.signal == RIUC_SIGNAL_SQ;
}

void parser4_set_on() {
    parser4.f_on = 1;
}
void parser4_set_off() {
    parser4.f_on = 0;
}
int parser4_is_on() {
    return parser4.f_on > 0;
}

void parser4_set_complete() {
    parser4.f_complete = 1;
}
void parser4_set_incomplete() {
    parser4.f_complete = 0;
}
int parser4_is_complete() {
    return parser4.f_complete == 1;
}

void parser4_set_port(char port) {
    parser4.port = port - '1';
}
int parser4_get_port() {
    return parser4.port;
}

void on_riuc4_data_received_default(char *buffer, int nbytes) {
    int i;
    for( i = 0; i < nbytes; i++ ) {
        switch (buffer[i]) {
        case 'L':
            parser4_set_ptt();
            parser4_set_parsing_port();
            parser4_set_incomplete();
            break;
        case 'Q':
            parser4_set_sq();
            parser4_set_parsing_port();
            parser4_set_incomplete();
            break;
        case 'T':
            parser4_set_tx();
            parser4_set_parsing_port();
            parser4_set_incomplete();
            break;
        case 'R':
            parser4_set_rx();
            parser4_set_parsing_port();
            parser4_set_incomplete();
            break;
        case 'E':
            parser4_set_error();
            parser4_clear_parsing_port();
            parser4_set_incomplete();
            break;
        case '0':
            if (parser4_is_parsing_port()) {
                parser4_clear_parsing_port();
                PJ_LOG(3, (__FILE__, 
                           "invalid parsed input: (%s) (%c) (%d)\n", buffer, buffer[i], buffer[i]));
            }
            else {
                parser4_set_complete();
                parser4_set_off();
            }
            break;
        case '1':
            if (parser4_is_parsing_port()) {
                parser4_clear_parsing_port();
                parser4_set_port(buffer[i]);
            }
            else {
                parser4_set_complete();
                parser4_set_on();
            }
            break;
        case '2':
        case '3':
        case '4':
            if (parser4_is_parsing_port()) {
                parser4_clear_parsing_port();
                parser4_set_port(buffer[i]);
            }
            else if(parser4_is_error()) {
                riuc4_error = buffer[i] - '0';
                parser4_set_complete();
            }
            else {
                PJ_LOG(3, (__FILE__, 
                           "invalid parsed input: (%s) (%c) (%d)\n", buffer, buffer[i], buffer[i]));
            }
            break;
        default:
            if (parser4_is_parsing_port()) {
                parser4_clear_parsing_port();
            }
            else if (parser4_is_error()) {
                riuc4_error = buffer[i] - '0';
                parser4_set_complete();
            }
            else {
                PJ_LOG(3, (__FILE__, 
                           "invalid parsed input: (%s) (%c) (%d)\n", buffer, buffer[i], buffer[i]));
            }
            break;
        }

        if( parser4_is_complete() ) {
            if (parser4_is_error()) {
                on_riuc_error(riuc4_error);
            }
            else {
                if( parser4_is_ptt() ) {
                    riuc4_status[parser4_get_port()].ptt = parser4_is_on();
                }
                else if (parser4_is_sq()) {
                    riuc4_status[parser4_get_port()].sq = parser4_is_on();
                }
                else if (parser4_is_tx()) {
                    riuc4_status[parser4_get_port()].tx = parser4_is_on();
                }
                else if (parser4_is_rx()) {
                    riuc4_status[parser4_get_port()].rx = parser4_is_on();
                }
                on_riuc_status(&(riuc4_status[parser4_get_port()]));
            }
        }
    }
}

void riuc4_init(void (*cb)(void *)) {
    on_serial_data_received = on_riuc4_data_received_default;
    process_command = riuc_process_command;
    on_riuc_error = on_riuc4_error_default;
    if( cb == NULL ) 
        on_riuc_status = on_riuc4_status_default;
    else 
        on_riuc_status = cb;
}

