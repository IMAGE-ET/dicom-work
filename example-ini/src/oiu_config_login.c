#include <string.h>
#include "oiu_config.h"

int login(char *username, char *password, oiu_config_t *config) 
{
	int i=0;
	for (i=0;i<config->n_users;i++) {
		if (strcmp(username, config->users[i].name)==0) {
			if (strcmp(password, config->users[i].password)==0) {
				return i; // return user index in config file	
			}
		}
	}
	return -1; // always return -1 if not
}

