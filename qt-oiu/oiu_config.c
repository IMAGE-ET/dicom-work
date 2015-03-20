#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "oiu_config.h"


int oiu_config (char *username, char *password, oiu_config_t *config) 
{
    //oiu_config_t config;
	
    if (ini_parse("oiu_config.ini", handler, config) < 0) {
        printf("Can't load 'oui_config.ini'\n");
        return -1;
    }
	int index;
	
	index = login(username, password, config);
	if (index != -1) {
		/*printf("User: %s\n",config->users[index].name);
		printf("Password: %s\n", config->users[index].password);
		printf("\trole name: %s \n", config->users[index].allow_roles[0]->name);
		printf("number: %d \n", config->users[index].allow_roles[0]->n_allow_nodes);
		int j=0;
		for (j=0;j<config->users[index].allow_roles[0]->n_allow_nodes;j++) {
			printf("\t\tnode name: %s \n", config->users[index].allow_roles[0]->allow_nodes[j]->name);
			printf("\t\t\tnode ip: %s \n", config->users[index].allow_roles[0]->allow_nodes[j]->ip);
			printf("\t\t\tnode port: %d \n", config->users[index].allow_roles[0]->allow_nodes[j]->port);
			
		}
		*/
		return index;

	} else {
		printf("invalid username and password");
		exit(1);
	}
    return 0;
}

int login(char *username, char *password, oiu_config_t *config) 
{
	int i=0;
	
	for (i=0;i<config->n_users;i++) {
		if (strcmp(username, config->users[i].name)==0 && strcmp(password, config->users[i].password)==0) {
			return i; // return user index in config file	
		}
	}
	return -1; // always return -1 if not
}

int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    oiu_config_t* pconfig = (oiu_config_t*)user;
	static int node_idx = -1;
	static int role_idx = -1;
	static int user_idx = -1;
	static int grp_idx = -1;
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
	else if (MATCH("node", "freg")) {
		pconfig->nodes[node_idx].freg = atof(value);
	}
	//processing group
	else if (MATCH("group", "name")) {
		grp_idx++;
		bzero(pconfig->grps[grp_idx].name, MAX_GRP_NAME_LEN); //make sure that string should be ended by '\0'
		strncpy(pconfig->grps[grp_idx].name, value, strlen(value)+1);
	}
	else if (MATCH("group", "allow_riu")) { 	//matching GRP with NODE

		char allow[MAX_NODE_NAME_LEN*MAX_N_NODES];
		strncpy(allow, value, strlen(value)+1);	
		char *p;
		// splitting string was separated by comma
		p = strtok(allow, ",");
		int numb_of_node_in_grp=0;
		while (p!=NULL) {
			int i=0;
			for (i=0;i<pconfig->n_nodes;i++) {
				if (strcmp(pconfig->nodes[i].name,p)==0) {
					pconfig->grps[grp_idx].allow_nodes[numb_of_node_in_grp] = &(pconfig->nodes[i]);
					pconfig->grps[grp_idx].n_allow_nodes=numb_of_node_in_grp+1;
					//printf ("%s", pconfig->grps[grp_idx].allow_nodes[numb_of_node_in_grp]->name);
					numb_of_node_in_grp++;
				}
			}
			p=strtok(NULL, ",");
		}
	}

	// processing role
	else if (MATCH("role", "name")) {
		role_idx++;
		bzero(pconfig->roles[role_idx].name, MAX_ROLE_NAME_LEN); //make sure that string should be ended by '\0'
		strncpy(pconfig->roles[role_idx].name, value, strlen(value)+1);
	}
	else if (MATCH("role", "allow_riu")) { 	//matching ROLE with NODE
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
	else if (MATCH("role","allow_grp")){
		char allow[MAX_GRP_NAME_LEN*MAX_N_GRPS];
		strncpy(allow, value, strlen(value)+1);	
		char *p;
		// splitting string was separated by comma
		p = strtok(allow, ",");
		int numb_of_grp_in_role=0;
		while (p!=NULL) {
			int i=0;
			for (i=0;i<pconfig->n_grps;i++) {
				if (strcmp(pconfig->grps[i].name,p)==0) {
					pconfig->roles[role_idx].allow_grps[numb_of_grp_in_role] = &(pconfig->grps[i]);
					pconfig->roles[role_idx].n_allow_grps=numb_of_grp_in_role+1;
					//printf("%s\n", pconfig->roles[role_idx].allow_grps[numb_of_grp_in_role]->name);
					numb_of_grp_in_role++;
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
	pconfig->n_grps=grp_idx+1;
    return 1;
}

