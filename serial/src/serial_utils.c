#include <fcntl.h>
#include <errno.h>
#include <termios.h>
//#include <pjlib.h>
#include <unistd.h>
#include "my-pjlib-utils.h"

void (*on_serial_data_received)(char *buffer, int nbytes);
void (*process_command)(int fd);

volatile int fQuit;

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

void serial_read_and_parse(int fd) {
    int nbytes;
    char buffer[10];
    memset(buffer, 0, sizeof(buffer));
    nbytes = read(fd, buffer, sizeof(buffer));
    if(nbytes > 0) {
        on_serial_data_received(buffer, nbytes);
        //on_riuc_status(&uart_status);
    }
}

static int do_thing(void *data) {
    //char *portdev = "/dev/cu.usbserial";
    //char *portdev = "/dev/ttyO1";
    
    int serial_fd;

    pj_thread_desc desc;
    pj_thread_t **thread;

    char *port_dev = (char *)data;
    struct termios options;
    CHECK(__FILE__, open_serial(port_dev, &serial_fd));
    config_serial(&options, serial_fd);

    // CHECK(__FILE__, pj_init());

    // pj_thread_register("riuc_thread", desc, thread);

    while(!fQuit) {
        serial_read_and_parse(serial_fd);
        process_command(serial_fd);
        pj_thread_sleep(100);
    }

    close(serial_fd);
    return 0;
}

void serial_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread) {
    fQuit = 0;
    pj_thread_create(pool, "serial_thread", do_thing, port_dev, PJ_THREAD_DEFAULT_STACK_SIZE, 0, thread);
}

void serial_end(pj_thread_t *thread) {
    fQuit = 1;
    pj_thread_join(thread);
}

