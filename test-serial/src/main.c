#include "riuc_uart.h"
#include "my-pjlib-utils.h"
void main_loop() {
    char temp[10];
    int fEnd = 0;
    while(!fEnd) {
        fgets(temp, sizeof(temp), stdin);
        switch (temp[0]) {
            case 's':
                    riuc_probe_sq();
                    break;
            case 'l':
                    riuc_probe_ptt();
                    break;
            case '+':
                    riuc_on_ptt();
                    break;
            case '-':
                    riuc_off_ptt();
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
void main_loop_4com() {
    char temp[10];
    int fEnd = 0;
    while(!fEnd) {
        fgets(temp, sizeof(temp), stdin);
        switch (temp[0]) {
            case 's':
                    riuc_probe_sq();
                    break;
            case 'l':
                    riuc_probe_ptt();
                    break;
            case '+':
                    riuc_on_ptt();
                    break;
            case '-':
                    riuc_off_ptt();
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
        PJ_LOG(1, ("Usage:", "myapp-riuc <device>"));
        pj_shutdown();
        exit(0);
    }
    pj_caching_pool_init(&cp, NULL, 4000);
    
    pool = pj_pool_create(&cp.factory, "serial_pool", 4000, 4000, NULL);

#ifndef RIUC4
    PJ_LOG(1, (__FILE__, "RIUC - 1COM"));
    riuc_init(NULL);
#else
    PJ_LOG(1, (__FILE__, "RIUC - 4COM - RIUC-ccp-v0.2"));
    exit(0);
    riuc4_init(NULL);
#endif

    riuc_start(pool, opts[1], &thread);

#ifndef RIUC4
    main_loop();
#else
    main_loop_4com();
#endif

    riuc_end(thread);

    pj_pool_release(pool);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();
    return 0;
}
