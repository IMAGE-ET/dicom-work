#include <stdio.h>
#include <string.h>
#include "oiu_config.h"
int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    oiu_config_t* pconfig = (oiu_config_t*)user;
	static int node_idx = -1;
	static int role_idx = -1;
	static int user_idx = -1;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("node", "name")) {
		node_idx++;
		bzero(pconfig->nodes[node_idx].name, MAX_NODE_NAME_LEN);
		strncpy(pconfig->nodes[node_idx].name, value, strlen(value) + 1);
    } 
	else if (MATCH("node", "ip")) {
		bzero(pconfig->nodes[node_idx].ip, MAX_IP_LEN);
		strncpy(pconfig->nodes[node_idx].ip, value, strlen(value) + 1);
    } 
	else if (MATCH("node", "port")) {
		pconfig->nodes[node_idx].port = atoi(value);
    }
	// processing role
	else if (MATCH("role", "name")) {
		role_idx++;
		bzero(pconfig->roles[role_idx].name, MAX_ROLE_NAME_LEN); //make sure that string should be ended by '\0'
		strncpy(pconfig->roles[role_idx].name, value, strlen(value)+1);
	}
	else if (MATCH("role", "allow")) { 	//matching ROLE with NODE
		char allow[MAX_NODE_NAME_LEN*MAX_N_NODES];
		strncpy(allow, value, strlen(value)+1);	
		char *p;
		// splitting string was separated by comma
		p = strtok(allow, ",");
		int numb_of_node_in_role=0;
		while (p!=NULL) {
			int i=0;
			for (i=0;i<pconfig->n_nodes;i++) {
				if (strcmp(pconfig->nodes[i].name,p)==0) {
					pconfig->roles[role_idx].allow_nodes[numb_of_node_in_role] = &(pconfig->nodes[i]);
					pconfig->roles[role_idx].n_allow_nodes=numb_of_node_in_role+1;
					numb_of_node_in_role++;
				}
			}
			p=strtok(NULL, ",");
		}
	}
	else if (MATCH("user", "name")) {
		user_idx++;
		bzero(pconfig->users[user_idx].name, MAX_USER_NAME_LEN);
		strncpy(pconfig->users[user_idx].name, value, strlen(value));
	}
	
	else if (MATCH("user", "role")) {
		char allow[MAX_ROLE_NAME_LEN];
		strncpy(allow, value, strlen(value)+1);	
		char *p;
		// splitting string was separated by comma
		p = strtok(allow, ",");
		while (p!=NULL) {
			int i=0;
			for (i=0;i<pconfig->n_nodes;i++) {
				if (strcmp(pconfig->roles[i].name,p)==0) {
					pconfig->users[user_idx].allow_roles[0] = &(pconfig->roles[i]);
					pconfig->users[user_idx].n_allow_roles=1; //an user has maximium a role
				}
			}
			p=strtok(NULL, ",");
		}
	}
	else if (MATCH("user", "password")) {
		strncpy(pconfig->users[user_idx].password, value, strlen(value)+1);
	}
	pconfig->n_nodes=node_idx+1;
	pconfig->n_roles=role_idx+1;
	pconfig->n_users=user_idx+1;
    return 1;
}
