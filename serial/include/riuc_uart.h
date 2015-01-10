#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <pjlib.h>
//#include <termios.h>
//pj_status_t open_serial(const char* portdev, int *p_fd);
//void config_serial(struct termios *options, int fd);
extern void (*on_riuc_status)(void *data);
extern void (*on_riuc_error)(int error_code);
extern void (*on_riuc_data_received)(char *buffer, int nbytes);

void riuc_init(void (*cb)(void *));
void riuc4_init(void (*cb)(void *));
void riuc_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread);
void riuc_end(pj_thread_t *thread);

void riuc_probe_sq();
void riuc_probe_ptt();

void riuc_on_ptt();
void riuc_off_ptt();
#endif
