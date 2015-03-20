#include "riuc4_uart.h"
#include "my-pjlib-utils.h"
void main_loop() {
    char temp[10];
    int fEnd = 0;
    int port_idx;
    while(!fEnd) {
        PJ_LOG(2, (__FILE__, "COMMAND:<port[1-4]><command[DdEertsl+-q]>:"));
        fgets(temp, sizeof(temp), stdin);
        port_idx = temp[0] - '1';
        if( port_idx < 0 || port_idx > 3 ) {
            PJ_LOG(2, (__FILE__, "Command error"));
            continue;
        }
        switch (temp[1]) {
            case 'D':
                    riuc4_disable_rx(port_idx);
                    break;
            case 'd':
                    riuc4_disable_tx(port_idx);
                    break;
            case 'E':
                    riuc4_enable_rx(port_idx);
                    break;
            case 'e':
                    riuc4_enable_tx(port_idx);
                    break;
            case 'r':
                    riuc4_probe_rx(port_idx);
                    break;
            case 't':
                    riuc4_probe_tx(port_idx);
                    break;
            case 's':
                    riuc4_probe_sq(port_idx);
                    break;
            case 'l':
                    riuc4_probe_ptt(port_idx);
                    break;
            case '+':
                    riuc4_on_ptt(port_idx);
                    break;
            case '-':
                    riuc4_off_ptt(port_idx);
                    break;
            case 'q':
                    fEnd = 1;
                    break;
            default:
                    PJ_LOG(3, (__FILE__, "Unknown command"));
                    break;
        }
    }
}
int main(int n, char *opts[]) {
    pj_caching_pool cp;
    pj_pool_t *pool;
    pj_thread_t *thread;

    pj_log_set_level(4);
    
    CHECK(__FILE__, pj_init());

    if(n < 2) {
        PJ_LOG(1, ("Usage:", "myapp-riuc4 <device>"));
        pj_shutdown();
        exit(0);
    }
    pj_caching_pool_init(&cp, NULL, 4000);
    
    pool = pj_pool_create(&cp.factory, "serial_pool", 4000, 4000, NULL);

    PJ_LOG(1, (__FILE__, "RIUC - 4COM - RIUC-ccp-v0.2"));
    riuc4_init(NULL);

    riuc4_start(pool, opts[1], &thread);

    main_loop();

    riuc4_end(thread);

    pj_pool_release(pool);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();
    return 0;
}
