#include "ini.h"
#include "pjlib.h"
#include "dicom-config.h"

static int port_index = 0;
static int maddr_index = 0;
void dicom_config_dump(dicom_config_t *pconfig) {
    PJ_LOG(3, (__FILE__, "control: %s:%d", pconfig->ctl_maddr, pconfig->ctl_port));
    int i = 0;
    for (i = i; i < port_index; i++) {
        PJ_LOG(3, (__FILE__, "%s: %s:%d", pconfig->stm_name[i], pconfig->stm_maddr[i], pconfig->stm_port[i]));
    }
}

static int parse_func(void *user, const char *section, const char *name, const char *value) {
    dicom_config_t *pconfig = (dicom_config_t *)user;
#define MATCH(s, n) ( (strncmp(s, section, strlen(s)) == 0) && (strncmp(n, name, strlen(n)) == 0) )
    if( MATCH("control", "port") ) {
        pconfig->ctl_port = atoi(value);
    }
    else if( MATCH("control", "maddr") ) {
        pconfig->ctl_maddr = strdup(value);
    }
    else if( MATCH("stream", "port") ) {
        pconfig->stm_port[port_index] = atoi(value);
        pconfig->stm_name[port_index] = strdup(section);
        port_index++;
    }
    else if( MATCH("stream", "maddr") ) {
        pconfig->stm_maddr[maddr_index++] = strdup(value);
    }
    else return 0;
    return 1;
}

void dicom_config_load(char *fname, dicom_config_t *pconfig) {
    if( ini_parse(fname, parse_func, pconfig) ) {
        PJ_LOG(1, (__FILE__, "Error parsing file %s", fname));
        exit(-1);
    }

    dicom_config_dump(pconfig);
}
int dicom_config_find(dicom_config_t *pconfig, const char *name) {
    int i = 0;
    for (i = 0; i < port_index; i++ ) {
        if(strncmp( pconfig->stm_name[i], name, pj_ansi_strlen(name)) == 0 ) {
            return i;
        }
    }
    return -1;
}
