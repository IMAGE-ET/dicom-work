#include "object-pool.h"
void opool_init(opool_t *p_opool, int capacity, int data_size, pj_pool_t *p_mempool) {
    int i;
    p_opool->items = pj_pool_zalloc(p_mempool, sizeof(opool_t) * capacity);
    p_opool->data = pj_pool_zalloc(p_mempool, data_size * capacity);
    p_opool->capacity = capacity;
    p_opool->data_size = data_size;
    p_opool->count = 0;

    for( i = 0; i < p_opool->capacity; i++ ) {
        p_opool->items[i].data = (void *)&(p_opool->data[i*data_size]);
    }
    pj_mutex_create_simple(p_mempool, "opool_mutex", &p_opool->p_mutex);
}

opool_item_t *opool_get(opool_t *p_opool) {
    opool_item_t *p_item = NULL;
    int i = 0;
    pj_mutex_lock(p_opool->p_mutex);

    if(p_opool->count == p_opool->capacity) {
        PJ_LOG(1, (__FILE__, "object pool is full"));
    }
    else {
        do {
            i = pj_rand() % p_opool->capacity;
            p_item = &(p_opool->items[i]);
        } while(p_item->is_used);
        PJ_LOG(4, (__FILE__, "Pick object at idx:%d", i));
        p_item->is_used = 1;
        ++(p_opool->count);
    }

    pj_mutex_unlock(p_opool->p_mutex);
    return p_item;
}

void opool_free(opool_t *p_opool, opool_item_t *p_item) {
    pj_mutex_lock(p_opool->p_mutex);
    p_item->is_used = 0;
    --(p_opool->count);
    pj_mutex_unlock(p_opool->p_mutex);
}
