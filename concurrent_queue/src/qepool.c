#include "queue.h"
void qepool_init(qepool_t *p_qepool, int capacity, int data_size, pj_pool_t *p_mempool) {
    int i;
    p_qepool->p_queue_events = pj_pool_zalloc(p_mempool, sizeof(queue_event_t) * capacity);
    p_qepool->__p_qe_data = pj_pool_zalloc(p_mempool, data_size * capacity);
    p_qepool->capacity = capacity;
    p_qepool->data_size = data_size;
    p_qepool->count = 0;

    for( i = 0; i < p_qepool->capacity; i++ ) {
        p_qepool->p_queue_events[i].data = (void *)&(p_qepool->__p_qe_data[i*data_size]);
    }
    pj_mutex_create_simple(p_mempool, "qepool_mutex", &p_qepool->p_mutex);
}

queue_event_t *qepool_get(qepool_t *p_qepool) {
    queue_event_t *p_event = NULL;
    int i = 0;
    pj_mutex_lock(p_qepool->p_mutex);

    if(p_qepool->count == p_qepool->capacity) {
        PJ_LOG(1, (__FILE__, "queue event pool is full"));
    }
    else {
        do {
            i = pj_rand() % p_qepool->capacity;
            p_event = &(p_qepool->p_queue_events[i]);
        } while(p_event->is_used);

        p_event->is_used = 1;
        ++(p_qepool->count);
    }

    pj_mutex_unlock(p_qepool->p_mutex);
    return p_event;
}

void qepool_free(qepool_t *p_qepool, queue_event_t *p_event) {
    pj_mutex_lock(p_qepool->p_mutex);
    p_event->is_used = 0;
    --(p_qepool->count);
    pj_mutex_unlock(p_qepool->p_mutex);
}
