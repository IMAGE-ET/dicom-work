#ifndef _IPVCCS_H_
#define _IPVCCS_H_

#include <pjsua-lib/pjsua.h>
#include "queue.h"
PJ_BEGIN_DECL

#define IPVCCS_RAND_SEED 12345
#define IPVCCS_QUEUE_LEN 100
/* IPVCCS Settings */
typedef struct ipvccs_cfg {
	char *user_name;
	char *domain;
	char *password;
	char *proxy;
} ipvccs_cfg_t;

/******** specific queue event ***************/
enum {
    INIT = 1001,
    CREATE_TRANSPORT,
    ACTIVATE_ACCOUNT,
    UPDATE_ACCOUNT,
    DEACTIVATE_ACCOUNT,
    REGISTER_ACCOUNT,
    UNREGISTER_ACCOUNT,
    MAKE_CALL,
    ANSWER_CALL,
    RING_CALL,
    REJECT_CALL,
    HANGUP_CALL,
    HANGUP_ALL_CALL,
    END_MARK
};

#define IPVCCS_FIELD_LEN 20
typedef union ipvccs_event_data {
    struct {
        int dummy;
    } e_init;

    struct {
        int dummy;
    } e_create_transport;
    
    struct {
        int dummy;
    } e_activate_account;
    
    struct {
        int dummy;
    } e_update_account;

    struct {
        int dummy;
    } e_deactivate_account;

    struct {
        int dummy;
    } e_register_account;

    struct {
        int dummy;
    } e_unregister_account;

    struct {
        char *user;
        char *domain;
    } e_make_call;

    struct {
        int call_id;
    } e_answer_call;

    struct {
        int call_id;
    } e_ring_call;

    struct {
        int call_id;
    } e_reject_call;

    struct {
        int call_id;
    } e_hangup_call;

    struct {
        int dummy;
    } e_hangup_all_call;
} ipvccs_event_data_t;

#define IPVCCS_QEDATA(qe) ((ipvccs_event_data_t *)(qe->data))

void ipvccs_event_init_init(queue_event_t *p_event);
void ipvccs_event_createtransport_init(queue_event_t *p_event);
void ipvccs_event_activateaccount_init(queue_event_t *p_event);
void ipvccs_event_updateaccount_init(queue_event_t *p_event);
void ipvccs_event_deactivateaccount_init(queue_event_t *p_event);
void ipvccs_event_registeraccount_init(queue_event_t *p_event);
void ipvccs_event_unregisteraccount_init(queue_event_t *p_event);
void ipvccs_event_makecall_init(queue_event_t *p_event, char *user, char *domain);
void ipvccs_event_answercall_init(queue_event_t *p_event, int call_id);
void ipvccs_event_ringcall_init(queue_event_t *p_event, int call_id);
void ipvccs_event_rejectcall_init(queue_event_t *p_event, int call_id);
void ipvccs_event_hangupcall_init(queue_event_t *p_event, int call_id);
void ipvccs_event_hangupallcall_init(queue_event_t *p_event);

/* QUEUE EVENT POOL */
typedef struct ipvccs_qepool {
    queue_event_t *p_queue_events;
    ipvccs_event_data_t *__p_qe_data;
    int capacity;
    int count;
    pj_mutex_t *p_mutex;
} ipvccs_qepool_t;

const char *ipvccs_event_name(int event_code);

void ipvccs_qepool_init(ipvccs_qepool_t *p_qepool, int capacity);
queue_event_t *ipvccs_qepool_get(ipvccs_qepool_t *p_qepool);
void ipvccs_qepool_free(ipvccs_qepool_t *p_qepool, queue_event_t *p_event);

pj_status_t ipvccs_init();
void ipvccs_run();
void ipvccs_destroy();

void ipvccs_cfg_init_default();

extern pj_pool_t *gp_pool;
extern pj_thread_desc g_ipvccs_clogic_thread_desc;
extern pj_thread_t *gp_ipvccs_clogic_thread;
extern ipvccs_cfg_t g_ipvccs_cfg;
//extern pj_status_t g_ipvccs_status;

PJ_END_DECL

#endif
