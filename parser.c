//
//  parser.c
//  sish
//
//  Created by Yanqiao Zhan on 12/12/15.
//  Copyright © 2015 Yanqiao Zhan. All rights reserved.
//

#include "parser.h"
void parser(Command*command,char*rawcommand){
    const char s[2]="|";
    char* subpath;
    Command*head=malloc(sizeof(Command));
    subpath=strtok(rawcommand,s);
    if(subpath==NULL)subpath="";
    head->argv=subpath;
    Command*cur=head;
    Command*prefix=head;
    while(subpath!=NULL){
        subpath=strtok(NULL, s);
        cur=malloc(sizeof(Command));
        cur->argv=subpath;
        prefix->next=cur;
        prefix=cur;
    }
}
