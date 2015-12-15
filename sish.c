/*
  sish.c
  sish

  Main Entry
  Created by Yanqiao Zhan on 12/10/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#include "sish.h"
 
void usage(){
    fprintf(stdout,"sish [ −x] [ −c command]\n\
            −c command\
            Execute the given command.\n\
            −x Enable tracing\n\
            Write each command to standard error, preceeded by ’+’\n");
    exit(EXIT_FAILURE);
}


int main(int argc, char ** argv) {
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
        handle(arg);
    }else{
        prompt(arg);
    }
    return 0;
}
