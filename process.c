/*
 process.c
 sish
 
 Created by Yanqiao Zhan on 12/12/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "process.h"
int exit_code;
char* getrestpart(char*full,char*prefix){
    int i,len1=(int)strlen(full),len2=(int)strlen(prefix);
    char*ret;
    for(i=len2;i<len1;i++){
        if(full[i]!=' '){
            break;
        }
    }
    ret=malloc(sizeof(char)*(len1-i+1));
    strncpy(ret, full+i, len1-i);
    return ret;
}

int spawn_proc (int in, int out, Command cmd){
    pid_t pid;
    char**splitedcommand=split(cmd.argv, " ");
    char*leftpart;
    if ((pid = fork ()) == 0){
        if (in != 0){
            dup2 (in, 0);
            close (in);
        }
        if (out != 1){
            dup2 (out, 1);
            close (out);
        }
        leftpart=getrestpart(cmd.argv, splitedcommand[0]);
        if(strcmp(splitedcommand[0], "echo")==0){
            echoCommand(leftpart);
        }else if(strcmp(splitedcommand[0],"cd")==0){
            cdCommand(leftpart);
        }else{
            exit_code=0;
            execvp (splitedcommand[0], (char * const *)splitedcommand);
            exit_code=127;
        }
    }
    
    return exit_code;
}
int fork_pipes (int n, Command cmd[]){
    int i;
    int in, fd [2];
    char**lastsplitedcommand;
    char*leftpart;
    in = 0;
    for (i = 0; i < n - 1; ++i){
        pipe (fd);
        spawn_proc (in, fd [1], cmd[i]);
        close (fd [1]);
        in = fd [0];
    }
    
    if (in != 0)
        dup2 (in, 0);
    lastsplitedcommand=split(cmd[i].argv, " ");
    
    leftpart=getrestpart(cmd[i].argv, lastsplitedcommand[0]);
    if(strcmp(lastsplitedcommand[0], "echo")==0){
        echoCommand(leftpart);
    }else if(strcmp(lastsplitedcommand[0],"cd")==0){
        cdCommand(leftpart);
    }else{
        execvp (lastsplitedcommand[0], (char * const *)lastsplitedcommand);
        if(errno==2)exit_code=127;
        else exit_code=errno;
        exit(exit_code);
    }
    return exit_code;
}


int handle(Arg*arg){
    
    Command allcommands[128];
    int n;
    pid_t pid;
    int index;
    int status;
    if((n=parser(arg->rawcommand,allcommands,arg))==-1){
        fprintf(stderr, "syntax error!\n");
        exit_code=127;
        return -1;
    }else if(n==0){
        exit(0);
    }
    if(arg->flag_x==1){
        index=0;
        for(index=0;index<n;index++){
            fprintf(stderr, "+ %s\n",allcommands[index].argv);
        }
    }
    if(arg->flag_d==1){
        if(daemon(1, 1)<0){
            fprintf(stderr, "Daemon fails!\n");
            exit_code=125;
            exit(EXIT_FAILURE);
        }
    }
    if((pid=fork())==0){
        fork_pipes(n, allcommands);
    }else if(pid>0){
        waitpid(pid,&status,0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)==127){
                fprintf(stderr, "%s: command not found\n",arg->rawcommand);
                exit_code=127;
            }
        }
        return exit_code;
    }
    return 0;
}