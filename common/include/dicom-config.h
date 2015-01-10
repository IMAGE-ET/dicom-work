#ifndef __DICOM_CONFIG_H__
#define __DICOM_CONFIG_H__
#define NETWORK_SIZE 10
typedef struct {
    const char *ctl_maddr;
    int ctl_port;
    const char *stm_name[NETWORK_SIZE];
    const char *stm_maddr[NETWORK_SIZE];
    int stm_port[NETWORK_SIZE];
} dicom_config_t;

void dicom_config_load(char *fname, dicom_config_t *pconfig);
int dicom_config_find(dicom_config_t *pconfig, const char *name);
#endif
