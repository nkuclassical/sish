/*
 prompt.c
 sish
 
 Created by Yanqiao Zhan on 12/10/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "prompt.h"


void prompt(Arg*arg){
    char input[1024];
    int exit_code=0;
    while(1){
        fprintf(stdout, "sish$ ");
        gets(input);
        arg->rawcommand=input;
        exit_code=handle(arg);
        if(exit_code==-1){
            break;
        }
        
    }
}
