#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
//#include <termios.h>
#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "serial_utils.h"

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

void (*on_riuc_status)(void *data);

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

inline void parser4_set_parsing_port() {
    parser4.f_parsing_port = 1;
}
inline void parser4_clear_parsing_port() {
    parser4.f_parsing_port = 0;
}
inline int parser4_is_parsing_port() {
    return parser4.f_parsing_port > 0;
}

inline void parser4_set_tx() {
    parser4.signal = RIUC_SIGNAL_TX;
}
inline void parser4_set_rx() {
    parser4.signal = RIUC_SIGNAL_RX;
}
inline void parser4_set_error() {
    parser4.signal = RIUC_SIGNAL_ERROR;
}
inline void parser4_set_ptt() {
    parser4.signal = RIUC_SIGNAL_PTT;
}
inline void parser4_set_sq() {
    parser4.signal = RIUC_SIGNAL_SQ;
}
inline int parser4_is_tx() {
    return parser4.signal == RIUC_SIGNAL_TX;
}
inline int parser4_is_rx() {
    return parser4.signal == RIUC_SIGNAL_RX;
}
inline int parser4_is_error() {
    return parser4.signal == RIUC_SIGNAL_ERROR;
}
inline int parser4_is_ptt() {
    return parser4.signal == RIUC_SIGNAL_PTT;
}
inline int parser4_is_sq() {
    return parser4.signal == RIUC_SIGNAL_SQ;
}
inline void parser4_set_on() {
    parser4.f_on = 1;
}
inline void parser4_set_off() {
    parser4.f_on = 0;
}
inline int parser4_is_on() {
    return parser4.f_on > 0;
}
inline void parser4_set_complete() {
    parser4.f_complete = 1;
}
inline void parser4_set_incomplete() {
    parser4.f_complete = 0;
}
inline int parser4_is_complete() {
    return parser4.f_complete == 1;
}
inline void parser4_set_port(char port) {
    parser4.port = port - '1';
}
inline int parser4_get_port() {
    return parser4.port;
}

void on_riuc4_data_received(char *buffer, int nbytes) {
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
                on_riuc4_error_default(riuc4_error);
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

/*
typedef struct _uart4_command_t {
    int fLED; // check PTT
    int fSQ;  // check SQ
    int fTX;  // check TX
    int fRX;  // check RX
    int enableTX;
    int enableRX;
    int disableTX;
    int disableRX;
    int onPTT;
    int offPTT;
} uart4_command_t;
*/

/*************************** COMMAND Format *******************
 |0   | 1   |2    | 3   | 4   | 5   | 6   | 7   |  8  |9     |10|11|12|13|14|15|
 |fLED| fSQ | fTX | fRX |entTX|entRX|disTX|disRX|onPTT|offPTT|  UNUSED         |
***********************************************************************************/
#define CMD_FLED    (0x1)
#define CMD_FSQ     (0x1 << 1)
#define CMD_FTX     (0x1 << 2)
#define CMD_FRX     (0x1 << 3)
#define CMD_ENT_TX  (0x1 << 4)
#define CMD_ENT_RX  (0x1 << 5)
#define CMD_DIS_TX  (0x1 << 6)
#define CMD_DIS_RX  (0x1 << 7)
#define CMD_ON_PTT  (0x1 << 8)
#define CMD_OFF_PTT (0x1 << 9)
struct {
    int command[4];
} uart4_command;

inline void set_check_ptt(int port_idx) {
    uart4_command.command[port_idx] |= CMD_FLED;
}
inline void set_check_sq(int port_idx) {
    uart4_command.command[port_idx] |= CMD_FSQ;
}
inline void set_check_tx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_FTX;
}
inline void set_check_rx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_FRX;
}
inline void set_enable_tx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_ENT_TX;
}
inline void set_disable_tx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_DIS_TX;
}
inline void set_enable_rx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_ENT_RX;
}
inline void set_disable_rx(int port_idx) {
    uart4_command.command[port_idx] |= CMD_DIS_RX;
}
inline void set_on_ptt(int port_idx) {
    uart4_command.command[port_idx] |= CMD_ON_PTT;
}
inline void set_off_ptt(int port_idx) {
    uart4_command.command[port_idx] |= CMD_OFF_PTT;
}

inline void reset_check_ptt(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_FLED;
}
inline void reset_check_sq(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_FSQ;
}
inline void reset_check_tx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_FTX;
}
inline void reset_check_rx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_FRX;
}
inline void reset_enable_tx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_ENT_TX;
}
inline void reset_disable_tx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_DIS_TX;
}
inline void reset_enable_rx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_ENT_RX;
}
inline void reset_disable_rx(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_DIS_RX;
}
inline void reset_on_ptt(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_ON_PTT;
}
inline void reset_off_ptt(int port_idx) {
    uart4_command.command[port_idx] &= ~CMD_OFF_PTT;
}

inline int is_check_ptt(int port_idx) {
    return uart4_command.command[port_idx] & CMD_FLED;
}
inline int is_check_sq(int port_idx) {
    return uart4_command.command[port_idx] & CMD_FSQ;
}
inline int is_check_tx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_FTX;
}
inline int is_check_rx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_FRX;
}
inline int is_enable_tx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_ENT_TX;
}
inline int is_disable_tx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_DIS_TX;
}
inline int is_enable_rx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_ENT_RX;
}
inline int is_disable_rx(int port_idx) {
    return uart4_command.command[port_idx] & CMD_DIS_RX;
}
inline int is_on_ptt(int port_idx) {
    return uart4_command.command[port_idx] & CMD_ON_PTT;
}
inline int is_off_ptt(int port_idx) {
    return uart4_command.command[port_idx] & CMD_OFF_PTT;
}

void do_check_ptt(int port_idx, int fd) {
    char data[] = "pttX\r";
    data[3] = port_idx + '1';
    write(fd, data, 5);
}
void do_check_sq(int port_idx, int fd) {
    char data[] = "sqX\r";
    data[2] = port_idx + '1';
    write(fd, data, 4);
}
void do_check_tx(int port_idx, int fd) {
    char data[] = "txX\r";
    data[2] = port_idx + '1';
    write(fd, data, 4);
}
void do_check_rx(int port_idx, int fd) {
    char data[] = "rxX\r";
    data[2] = port_idx + '1';
    write(fd, data, 4);
}
void do_enable_tx(int port_idx, int fd) {
    char data[] = "entxX\r";
    data[4] = port_idx + '1';
    write(fd, data, 6);
}
void do_disable_tx(int port_idx, int fd) {
    char data[] = "distxX\r";
    data[5] = port_idx + '1';
    write(fd, data, 7);
}
void do_enable_rx(int port_idx, int fd) {
    char data[] = "enrxX\r";
    data[4] = port_idx + '1';
    write(fd, data, 6);
}
void do_disable_rx(int port_idx, int fd) {
    char data[] = "disrxX\r";
    data[5] = port_idx + '1';
    write(fd, data, 7);
}
void do_on_ptt(int port_idx, int fd) {
    char data[] = "onpttX\r";
    data[5] = port_idx + '1';
    write(fd, data, 7);
}
void do_off_ptt(int port_idx, int fd) {
    char data[] = "offpttX\r";
    data[6] = port_idx + '1';
    write(fd, data, 8);
}

void riuc4_process_command(int fd) {
    int i;
    for( i = 0; i < N_RIUC; i++ ) {
        if (is_check_ptt(i)) {
            reset_check_ptt(i);
            do_check_ptt(i, fd);
        }
        if (is_check_sq(i)) {
            reset_check_sq(i);
            do_check_sq(i, fd);
        }
        if (is_check_tx(i)) {
            reset_check_tx(i);
            do_check_tx(i, fd);
        }
        if (is_check_rx(i)) {
            reset_check_rx(i);
            do_check_rx(i, fd);
        }
        if (is_enable_tx(i)) {
            reset_enable_tx(i);
            do_enable_tx(i, fd);
        }
        if (is_disable_tx(i)) {
            reset_disable_tx(i);
            do_disable_tx(i, fd);
        }
        if (is_enable_rx(i)) {
            reset_enable_rx(i);
            do_enable_rx(i, fd);
        }
        if (is_disable_rx(i)) {
            reset_disable_rx(i);
            do_disable_rx(i, fd);
        }
        if (is_on_ptt(i)) {
            reset_on_ptt(i);
            do_on_ptt(i, fd);
        }
        if (is_off_ptt(i)) {
            reset_off_ptt(i);
            do_off_ptt(i, fd);
        }
    }
}

void riuc4_init(void (*cb)(void *)) {
    on_serial_data_received = on_riuc4_data_received;
    process_command = riuc4_process_command;
    //on_riuc_error = on_riuc4_error_default;
    if( cb == NULL ) 
        on_riuc_status = on_riuc4_status_default;
    else 
        on_riuc_status = cb;
}

void riuc4_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread) {
    uart4_command.command[0] = 0;
    uart4_command.command[1] = 0;
    uart4_command.command[2] = 0;
    uart4_command.command[3] = 0;
    serial_start(pool, port_dev, thread);
}

void riuc4_end(pj_thread_t *thread) {
    serial_end(thread);
}

void riuc4_probe_sq(int port_idx) {
    set_check_sq(port_idx);
}
void riuc4_probe_ptt(int port_idx) {
    set_check_ptt(port_idx);
}
void riuc4_probe_tx(int port_idx) {
    set_check_tx(port_idx);
}
void riuc4_probe_rx(int port_idx) {
    set_check_rx(port_idx);
}
void riuc4_enable_tx(int port_idx) {
    set_enable_tx(port_idx);
}
void riuc4_disable_tx(int port_idx) {
    set_disable_tx(port_idx);
}
void riuc4_enable_rx(int port_idx) {
    set_enable_rx(port_idx);
}
void riuc4_disable_rx(int port_idx) {
    set_disable_rx(port_idx);
}
void riuc4_on_ptt(int port_idx) {
    set_on_ptt(port_idx);
}
void riuc4_off_ptt(int port_idx) {
    set_off_ptt(port_idx);
}
