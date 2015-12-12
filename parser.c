/*
  parser.c
  sish

  Created by Yanqiao Zhan on 12/12/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#include "parser.h"
int parser(char*rawcommand,Arg*arg){
    const char s[2]="|";
    char* subpath;
    fprintf(stdout, "raw:%s\n",rawcommand);
/*    Command*head=malloc(sizeof(Command));
    Command*cur;
    Command*prefix;*/
    subpath=strtok(rawcommand,s);
    while(subpath!=NULL){
        if(arg->flag_x==1){
            fprintf(stdout, "+ %s\n",subpath);
        }
/*        cur=malloc(sizeof(Command));
        cur->argv=subpath;
        prefix->next=cur;
        prefix=cur;*/
        subpath=strtok(NULL, s);
    }
    return 0;
}
