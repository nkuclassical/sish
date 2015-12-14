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
char*translatepath(char*path){
    char*result=malloc(sizeof(char)*(strlen(path)+10));
    char*temp=malloc(sizeof(char)*(strlen(path)));
    strcpy(result, "/home/");
    memcpy(temp, &path[1], strlen(path)-1);
    strcat(result, temp);
    return result;
}
char*translatepath2(char*path){
    char*result;
    char*temp=malloc(sizeof(char)*(strlen(path)));
    char*username;
    username=malloc(sizeof(char)*strlen(getenv("HOME")));
    strncpy(username, getenv("HOME"), strlen(getenv("HOME")));
    temp=malloc(sizeof(char)*(strlen(path)+10));
    result=malloc(sizeof(char)*(strlen(path)+10+strlen(username)));
    strcpy(result, username);
    memcpy(temp, &path[1], strlen(path)-1);
    strcat(result, temp);
    return result;
}
int cdCommand(char *path){

    char*envhome;
    char**subpath;
    struct stat s;
            envhome=getenv("HOME");
    if(strlen(path)==0){

        if(envhome==NULL){
            fprintf(stdout, "cd: HOME not set\n");
            exit_code=1;
            return -1;
        }else{
            path=malloc(sizeof(char)*strlen(envhome));
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
    
    if(stat(path, &s)==-1){
        fprintf(stderr, "cd: %s: No such file or directory\n",path);
        exit_code=1;
    }else{
        if(S_ISDIR(s.st_mode)){
            if(chdir(path) < 0){
                fprintf(stderr,"cd: %s: No such file or directory!\n",path);
                exit_code=1;
            }else{
                exit_code=0;
            }
        }else{
            fprintf(stderr, "cd: %s: Not a directory\n",path);
            exit_code=1;
        }
    }
    
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
    fflush(stdout);
    exit_code=0;
    
    return 0;
}




