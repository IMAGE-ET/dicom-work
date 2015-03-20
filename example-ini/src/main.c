#include <stdio.h>
#include "oiu_config.h"
#include "ini.h"
#include <string.h>
int main(int argc, char* argv[])
{
    oiu_config_t config;
    if (ini_parse("oiu_config.ini", handler,&config) < 0) {
        printf("Can't load 'oui_config.ini'\n");
        return 1;
    }
	int i=0;
	for (i=0;i<config.n_users;i++) {
		printf("User: %s\n",config.users[i].name);
		printf("Password: %s\n", config.users[i].password);
		printf("\trole name: %s \n", config.users[i].allow_roles[0]->name);
		int j=0;
		for (j=0;j<config.users[i].allow_roles[0]->n_allow_nodes;j++) {
			printf("\t\tnode name: %s \n", config.users[i].allow_roles[0]->allow_nodes[j]->name);
			printf("\t\t\tnode ip: %s \n", config.users[i].allow_roles[0]->allow_nodes[j]->ip);
			printf("\t\t\tnode port: %d \n", config.users[i].allow_roles[0]->allow_nodes[j]->port);
		}
		printf ("\n-----------------------\n");
	}
    return 0;
}

