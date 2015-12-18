/*
 prompt.c
 sish
 
 Created by Yanqiao Zhan on 12/10/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "prompt.h"


void avoidctrlc(){
    fprintf(stdout,"\n");
}
void prompt(Arg*arg){
    char input[1024];
    while(1){
        signal(SIGINT,avoidctrlc);/*SIGINT is produced by Ctrl+C*/
        fprintf(stdout, "sish$ ");
        fgets(input,1024,stdin);
        input[strlen(input)-1]='\0';/*remove \n tag */
        if(strlen(input)==0){
            continue;
        }
        arg->rawcommand=input;
        handle(arg);
    }
}
