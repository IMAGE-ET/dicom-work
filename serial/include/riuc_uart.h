#ifndef __SERIAL_RIUC_H__
#define __SERIAL_RIUC_H__
#include <pjlib.h>
extern void (*on_riuc_status)(void *data);
extern void (*on_riuc_error)(int error_code);

// DEFAULT ACTIONS : INIT, START, END
void riuc_init(void (*cb)(void *));
void riuc4_init(void (*cb)(void *));
void riuc_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread);
void riuc_end(pj_thread_t *thread);

// RIUC COMMAND PROCESSING LOGIC
void riuc_process_command(int fd);

// SPECIFIC RIUC COMMANDS
void riuc_probe_sq(); // Probe SQ status
void riuc_probe_ptt(); // Probe PTT status

void riuc_on_ptt(); // Turn PTT on
void riuc_off_ptt(); // Turn PTT off
#endif
