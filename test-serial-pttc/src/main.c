#include "pttc_uart.h"
#include "my-pjlib-utils.h"
#include "ansi_utils.h"

int main(int n, char *opts[]) {
    pj_caching_pool cp;
    pj_pool_t *pool;
    pj_thread_t *thread;

    pj_log_set_level(4);
    
    CHECK(__FILE__, pj_init());

    if(n < 2) {
        PJ_LOG(1, ("Usage:", "myapp-pttc <device>"));
        pj_shutdown();
        exit(0);
    }
    pj_caching_pool_init(&cp, NULL, 4000);
    
    pool = pj_pool_create(&cp.factory, "serial_pool", 4000, 4000, NULL);

    PJ_LOG(1, (__FILE__, "PTTC over UART"));
    pttc_init(NULL);

    pttc_start(pool, opts[1], &thread);
    
    my_pause();

    pttc_end(thread);

    pj_pool_release(pool);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();
    return 0;
}
