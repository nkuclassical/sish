/*
  sish.c
  sish

  Main Entry
  Created by Yanqiao Zhan on 12/10/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "prompt.h"
#include "parser.h"

void usage(){
    fprintf(stdout,"sish [ −x] [ −c command]\n\
            −c command\
            Execute the given command.\n\
            −x Enable tracing\n\
            Write each command to standard error, preceeded by ’+’\n");
}


int main(int argc, char ** argv) {
    // insert code here...
    Arg*arg=malloc(sizeof(Arg));
    char ch;
    if(argc==1){
        arg->flag_c=0;
        arg->flag_x=0;
    }
    while((ch=getopt(argc,argv,"xc:"))!=-1){
        switch(ch){
            case 'c':
                arg->flag_c=1;
                arg->rawcommand=optarg;
                break;
            case 'x':
                arg->flag_x=1;
                break;
        }
    }
    
    if((arg->rawcommand!=NULL)){
        prompt();
    }else{
        Command*command;
        parser(command, arg->rawcommand);
    }
    return 0;
}
