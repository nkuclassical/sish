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
    if ((pid = fork ()) == 0){
        if (in != 0){
            dup2 (in, 0);
            close (in);
        }
        if (out != 1){
            dup2 (out, 1);
            close (out);
        }
        
        if(cmd.flag_a==1){
            freopen(cmd.appendfilepath, "a", stdout);

        }else if(cmd.flag_o==1){
            freopen(cmd.outfilepath, "w", stdout);
            printf("stdout change w, command%s  path%s\n",cmd.argv,cmd.outfilepath);
        }
        if(cmd.flag_i==1){
            freopen(cmd.infilepath, "r", stdin);
        }
        exit_code=0;
        execvp (splitedcommand[0], (char * const *)splitedcommand);
        exit_code=127;
        exit(exit_code);
    }
    
    return exit_code;
}
int fork_pipes (int n, Command cmd[]){
    int i;
    int in, fd [2];
    char**lastsplitedcommand;
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
    if(cmd[i].flag_a==1){
        freopen(cmd[i].appendfilepath, "a", stdout);
    }else if(cmd[i].flag_o==1){
        freopen(cmd[i].outfilepath, "w", stdout);
        printf("stdout change w, command%s  path%s\n",cmd[i].argv,cmd[i].outfilepath);
    }
    if(cmd[i].flag_i==1){
        freopen(cmd[i].infilepath, "r", stdin);
    }
    printf("haha %s\n",cmd[i].outfilepath);
    execvp (lastsplitedcommand[0], (char * const *)lastsplitedcommand);
    if(errno==2)exit_code=127;
    else exit_code=errno;
    exit(exit_code);
    
    return exit_code;
}


int handle(Arg*arg){
    
    Command allcommands[128];
    int n;
    pid_t pid;
    int index;
    char**splitedcommand;
    char*leftpart;
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
    
    
    
    splitedcommand=split(allcommands[0].argv, " ");
    
    leftpart=getrestpart(allcommands[0].argv, splitedcommand[0]);
    
    
    if(strcmp(splitedcommand[0], "echo")==0){
        
        echoCommand(leftpart);
        
    }else if(strcmp(splitedcommand[0],"cd")==0){
        cdCommand(leftpart);
    }else{
        if((pid=fork())==0){
            fork_pipes(n, allcommands);
            exit(exit_code);
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
    }
    
    return 0;
}