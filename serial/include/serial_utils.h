#ifndef __SERIAL_UTILS_H__
#define __SERIAL_UTILS_H__
#include <termios.h>
#include <pjlib.h>
extern void (*on_serial_data_received)(char *buffer, int nbytes);
extern void (*process_command)(int fd);

pj_status_t open_serial(const char* portdev, int *p_fd);
void config_serial(struct termios *options, int fd);
void serial_read_and_parse(int fd);
//int do_thing(void *data);
void serial_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread);
void serial_end(pj_thread_t *thread);
#endif
