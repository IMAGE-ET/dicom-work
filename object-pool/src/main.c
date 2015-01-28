#include <pjlib.h>
#include "my-pjlib-utils.h"
#include "object-pool.h"

opool_t opool;
const char *s = "Cong hoa xa hoi chu nghia";

int do_test(void *user) {
    int i;
    pj_pool_t *pool = (pj_pool_t *)user;
    opool_init(&opool, 10, strlen(s)+10, pool);
    for (i = 0; i < 100; i++) {
        opool_item_t *p_item = opool_get(&opool);
        pj_memcpy(p_item->data, s, strlen(s));
        printf("%d: %s\n", i, p_item->data);
        pj_thread_sleep(pj_rand()%100);
        opool_free(&opool, p_item);
    }
    return 0;
}

int main() {
    pj_caching_pool cp;
    pj_pool_t *pool;
    int i;
    pj_thread_t *thread1;
    
    pj_log_set_level(3);
    CHECK(__FILE__, pj_init());
    pj_srand(123765);
    pj_caching_pool_init(&cp, NULL, 1024);

    pool = pj_pool_create(&cp.factory, "objpool", 128, 128, NULL);

    pj_thread_create(pool, "thread1", &do_test, pool, PJ_THREAD_DEFAULT_STACK_SIZE, 0, &thread1);
    pj_thread_sleep(500);
    do_test(pool);

    pj_thread_join(thread1);

    pj_pool_release(pool);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();
    return 0;
}
