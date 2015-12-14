/*
  builtin.c
  sish

  Created by Yanqiao Zhan on 12/10/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


#include "builtin.h"
/*
 Handle cd echo exit
 */

int exit_code;
int cdCommand(char *path){
    /*
     Undo
     need to supportc 'cd ~' 

     */
    char*envhome;
    if(strlen(path)==0){
        envhome=getenv("HOME");
        if(envhome==NULL){
            fprintf(stdout, "cd: HOME not set\n");
            exit_code=1;
            return -1;
        }else{
            path=malloc(sizeof(char)*strlen(envhome));
            strncpy(path, envhome, strlen(envhome));
        }
    }
    if(access(path,R_OK)!=0){
        fprintf(stderr,"cd: %s: Permission denied\n",path);
        exit_code=1;
        return -1;
    }
    if(chdir(path) < 0){
        fprintf(stderr,"cd: %s: No such file or directory!\n",path);
        exit_code=1;
        return -1;
    }
    /*
     return 0 if change directory successfully.
     */
    return 0;
}
int echoCommand(char *message){
    pid_t pid;
    if (strcmp(message,"$$") == 0) {
        pid = getpid();
        fprintf(stdout, "%d\n",pid);
    }else if (strcmp(message, "$?") == 0) {
        fprintf(stdout, "%d\n",exit_code);
    }else fprintf(stdout,"%s\n", message);
    exit_code=0;
    return 0;
}




