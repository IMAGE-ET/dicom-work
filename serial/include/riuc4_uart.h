#ifndef __RIUC4_UART_H__
#define __RIUC4_UART_H__
#include <pjlib.h>
extern void (*on_riuc4_status)(void *data);
extern void (*on_riuc4_error)(int error_code);

// DEFAULT ACTIONS : INIT, START, END
void riuc4_init(void (*cb)(void *));
void riuc4_start(pj_pool_t *pool, char *port_dev, pj_thread_t **thread);
void riuc4_end(pj_thread_t *thread);

// RIUC COMMAND PROCESSING LOGIC
void riuc4_process_command(int fd);

// SPECIFIC RIUC COMMANDS
void riuc4_probe_sq(int port_idx); // Probe SQ status
void riuc4_probe_ptt(int port_idx); // Probe PTT status
void riuc4_probe_tx(int port_idx);
void riuc4_probe_rx(int port_idx);

void riuc4_enable_tx(int port_idx);
void riuc4_disable_tx(int port_idx);

void riuc4_enable_rx(int port_idx);
void riuc4_disable_rx(int port_idx);

void riuc4_on_ptt(int port_idx); // Turn PTT on
void riuc4_off_ptt(int port_idx); // Turn PTT off
#endif
