#ifndef __DICOM_CONFIG_H__
#define __DICOM_CONFIG_H__
#define NETWORK_SIZE 10
/*typedef struct {
    const char *ctl_maddr;
    int ctl_port;
    const char *stm_name[NETWORK_SIZE];
    const char *stm_maddr[NETWORK_SIZE];
    int stm_port[NETWORK_SIZE];
} dicom_config_t;
*/

typedef struct {
    const char *ipmaddr;
    int port;
} dicom_group_t;

typedef struct {
    const char *ip;
    int port;
} dicom_node_t;

typedef struct {
    dicom_group_t ptt_group;
    dicom_node_t arbiter;
} dicom_config_t;

void dicom_config_load(char *fname, dicom_config_t *pconfig);
#endif
