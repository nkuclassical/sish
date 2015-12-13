/*
 process.c
 sish
 
 Created by Yanqiao Zhan on 12/12/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "process.h"

int spawn_proc (int in, int out, Command cmd){
    pid_t pid;
    char**splitedcommand=split(cmd.argv, " ");
    if ((pid = fork ()) == 0){
        if (in != 0){
            dup2 (in, 0);
            close (in);
        }
        
        if (out != 1){
            dup2 (out, 1);
            close (out);
        }
        return execvp (splitedcommand[0], (char * const *)splitedcommand);
    }
    
    return pid;
}
int
fork_pipes (int n, Command cmd[]){
    int i;
    int in, fd [2];
    char**lastsplitedcommand;
    in = 0;
    for (i = 0; i < n - 1; ++i)
    {
        pipe (fd);
        spawn_proc (in, fd [1], cmd[i]);
        close (fd [1]);
        in = fd [0];
    }
    
    if (in != 0)
        dup2 (in, 0);
    lastsplitedcommand=split(cmd[i].argv, " ");
    return execvp (lastsplitedcommand[0], (char * const *)lastsplitedcommand);
}


int handle(Arg*arg){
    
    Command allcommands[128];
    int n;
    pid_t pid;
    int status;
    int index;
    if((pid=fork())==0){
        if((n=parser(arg->rawcommand,allcommands))==0){
            fprintf(stderr, "Parse raw command error!\n");
            exit(EXIT_FAILURE);
        }
        if(arg->flag_x==1){
            index=0;
            for(index=0;index<n;index++){
                fprintf(stderr, "+ %s\n",allcommands[index].argv);
            }
        }
        fork_pipes(n, allcommands);
    }else if(pid>0){
        waitpid(pid, &status, 0);
    }
    return 0;
}