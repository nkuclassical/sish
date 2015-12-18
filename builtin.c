/*
 builtin.c
 sish
 
 Created by Yanqiao Zhan on 12/10/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */



#include "builtin.h"
/*
 Handle cd echo exit
 */

int exit_code;

/*handle normal cd case*/
char*translatepath(char*path){
    char*result=Malloc(sizeof(char)*(strlen(path)+10));
    char*temp=Malloc(sizeof(char)*(strlen(path)));
    strcpy(result, "/home/");
    memcpy(temp, &path[1], strlen(path)-1);
    strcat(result, temp);
    return result;
}

/*handle cd ~[username]/ */
char*translatepath2(char*path){
    char*result;
    char*temp=Malloc(sizeof(char)*(strlen(path)));
    char*username;
    username=Malloc(sizeof(char)*strlen(getenv("HOME")));
    strncpy(username, getenv("HOME"), strlen(getenv("HOME")));
    temp=Malloc(sizeof(char)*(strlen(path)+10));
    result=Malloc(sizeof(char)*(strlen(path)+10+strlen(username)));
    strcpy(result, username);
    memcpy(temp, &path[1], strlen(path)-1);
    strcat(result, temp);
    return result;
}
int cdCommand(char *path){
    
    char*envhome;
    char**subpath;
    envhome=getenv("HOME");
    if(strlen(path)==0){
        if(envhome==NULL){
            fprintf(stdout, "cd: HOME not set\n");
            exit_code=1;
            return -1;
        }else{
            path=Malloc(sizeof(char)*strlen(envhome));
            strncpy(path, envhome, strlen(envhome));
        }
    }
    
    
    if(path[0]=='~'){
        subpath=split(path, "/");
        if(strcmp(subpath[0],"~")==0){
            if(envhome==NULL){
                fprintf(stdout, "cd: HOME not set\n");
                exit_code=1;
                return -1;
            }
            path=translatepath2(path);
        }else{
            path=translatepath(path);
        }
    }

    /*
        errno meaning of chdir http://www.gnu.org/software/libc/manual/html_node/File-Name-Errors.html#File-Name-Errors
     */
    if(chdir(path) < 0){
        exit_code=errno;
        switch (errno) {
            case EACCES:
                fprintf(stderr, "cd: %s: Permission Denied!\n",path);
                break;
            case ENOENT:
                fprintf(stderr,"cd: %s: No such file or directory!\n",path);
                break;
            case ENOTDIR:
                fprintf(stderr, "cd: %s: It is not a directory!\n",path);
                break;
            case ELOOP:
                fprintf(stderr, "cd: %s: Too many symbolic links were solved!\n",path);
            default:
                fprintf(stderr, "cd: %s: Failed to change directory!\n",path);
                break;
        }
    }
    exit_code=0;
    return 0;
}

int echoCommand(char *message){
    pid_t pid;
    if (strcmp(message,"$$") == 0) {
        pid = getpid();
        fprintf(stdout, "%d\n",pid);
    }else if (strcmp(message, "$?") == 0) {
        fprintf(stdout, "%d\n",exit_code);
    }else{
        if(strlen(message)>2&&(message[0]=='-'&&message[1]=='n')){
            fprintf(stdout, "%s",message);
        }else fprintf(stdout,"%s\n", message);
    }
    fflush(stdout);
    exit_code=0;
    return 0;
}




