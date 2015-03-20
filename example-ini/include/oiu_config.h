#ifndef __OIU_CONFIG_H__
#define __OIU_CONFIG_H__

#define MAX_N_NODES 10
#define MAX_N_ROLES 3
#define MAX_N_USERS 30
#define MAX_NODE_NAME_LEN 20
#define MAX_USER_NAME_LEN 20
#define MAX_ROLE_NAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_IP_LEN 20

typedef struct {
	char name[MAX_NODE_NAME_LEN];
	//char *name;
	char ip[MAX_IP_LEN];
	int port;
} node_config_t;

typedef struct {
	char name[MAX_ROLE_NAME_LEN];
	node_config_t *allow_nodes[MAX_N_NODES];
	int n_allow_nodes;
} role_config_t;

typedef struct {
	char name[MAX_USER_NAME_LEN];
	char password[MAX_PASSWORD_LEN];
	int n_allow_roles;
	role_config_t *allow_roles[MAX_N_ROLES];
} user_config_t;


typedef struct {
	node_config_t nodes[MAX_N_NODES];
	role_config_t roles[MAX_N_ROLES];
	user_config_t users[MAX_N_USERS];
	int n_nodes;
	int n_roles;
	int n_users;
} oiu_config_t;
int handler(void* user, const char* section, const char* name, const char* value);
//int login(char *username, char *password, oiu_config_t *config); 

#endif
