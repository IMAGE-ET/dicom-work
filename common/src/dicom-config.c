#include "ini.h"
#include "pjlib.h"
#include "dicom-config.h"

static int port_index = 0;
static int maddr_index = 0;
void dicom_config_dump(dicom_config_t *pconfig) {
    PJ_LOG(3, (__FILE__, "control: %s:%d", pconfig->ptt_group.ipmaddr, pconfig->ptt_group.port));
}

static int parse_func(void *user, const char *section, const char *name, const char *value) {
    dicom_config_t *pconfig = (dicom_config_t *)user;
#define MATCH(s, n) ( (strncmp(s, section, strlen(s)) == 0) && (strncmp(n, name, strlen(n)) == 0) )
    if( MATCH("group-ptt", "port") ) {
        pconfig->ptt_group.port = atoi(value);
    }
    else if( MATCH("group-ptt", "ipmaddr") ) {
        pconfig->ptt_group.ipmaddr = strdup(value);
    }
    else if( MATCH("arbiter", "ip") ) {
        pconfig->arbiter.ip = strdup(value);
    }
    else if( MATCH("arbiter", "port") ) {
        pconfig->arbiter.port = atoi(value);
    }
    return 1;
}

void dicom_config_load(char *fname, dicom_config_t *pconfig) {
    if( ini_parse(fname, parse_func, pconfig) ) {
        PJ_LOG(1, (__FILE__, "Error parsing file %s", fname));
        exit(-1);
    }

    dicom_config_dump(pconfig);
}

