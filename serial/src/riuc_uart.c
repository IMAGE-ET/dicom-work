#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <pjlib.h>
#include "my-pjlib-utils.h"

volatile int onPTT;
volatile int offPTT;

volatile int fLED;
volatile int fSQ;
volatile int fQuit;

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

int riuc_fd;

void (*on_riuc_status)(void *data);
void (*on_riuc_error)(int error_code);
void (*on_riuc_data_received)(char *buffer, int nbytes);

pj_status_t open_serial(char* portdev, int *p_fd) {
    //*p_fd = open(portdev, O_RDWR | O_NOCTTY | O_NONBLOCK);
    *p_fd = open(portdev, O_RDWR | O_NOCTTY);
    if( (*p_fd) < 0 ) {
        PJ_LOG(3, (__FILE__, "Cannot open port: %s", strerror(errno)));
        return PJ_SUCCESS - 100;
    }
    fcntl(*p_fd, F_SETFL, 0);
    return PJ_SUCCESS;
}

void config_serial(struct termios *options, int fd) {
    tcgetattr(fd, options);

    cfsetispeed(options, B9600);
    cfsetospeed(options, B9600);

    options->c_cflag |= (CREAD |CLOCAL);
    options->c_cflag &= ~CSIZE; /* Mask the character size bits */
    options->c_cflag |= CS8;    /* Select 8 data bits */
    options->c_cflag &= ~CRTSCTS;
    options->c_iflag &= ~(IXON | IXOFF | IXANY);
    //options->c_lflag |= (ICANON | ECHO | ECHOE); // Canonical mode

    options->c_lflag &= ~(ICANON | ECHO); // RAW mode
    options->c_cc[VMIN] = 0;
    options->c_cc[VTIME] = 0; // measured in 0.1 second

    tcsetattr(fd, TCSANOW, options);
}

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

void serial_read_and_parse(int fd) {
    int nbytes;
    char buffer[10];
    memset(buffer, 0, sizeof(buffer));
    nbytes = read(fd, buffer, sizeof(buffer));
    if(nbytes > 0) {
        on_riuc_data_received(buffer, nbytes);
        //on_riuc_status(&uart_status);
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

int do_thing(void *data) {
    //char *portdev = "/dev/cu.usbserial";
    //char *portdev = "/dev/ttyO1";
    
    pj_thread_desc desc;
    pj_thread_t **thread;

    char *port_dev = (char *)data;
    struct termios options;
    CHECK(__FILE__, open_serial(port_dev, &riuc_fd));
    config_serial(&options, riuc_fd);

    // CHECK(__FILE__, pj_init());

    // pj_thread_register("riuc_thread", desc, thread);

    fLED = 0;
    fSQ = 0;
    fQuit = 0;
    while(!fQuit) {
        serial_read_and_parse(riuc_fd);
        if (fLED) {
            fLED = 0;
            probLED(riuc_fd);
        }
        if (fSQ) {
            fSQ = 0;
            probSQ(riuc_fd);
        }
        if (onPTT) {
            onPTT = 0;
            on_ptt(riuc_fd);
        }
        if (offPTT) {
            offPTT = 0;
            off_ptt(riuc_fd);
        }
        pj_thread_sleep(100);
    }

    close(riuc_fd);
    return 0;
}

void riuc_init(void (*cb)(void *)) {
    on_riuc_data_received = on_riuc_data_received_default;
    if( cb == NULL ) 
        on_riuc_status = on_riuc_status_default;
    else 
        on_riuc_status = cb;
}

void riuc_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread) {
    pj_thread_create(pool, "serial_thread", do_thing, port_dev, PJ_THREAD_DEFAULT_STACK_SIZE, 0, thread);
}

void riuc_end(pj_thread_t *thread) {
    fQuit = 1;
    pj_thread_join(thread);
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

