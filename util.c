/*
 util.c
 sish
 
 Created by Yanqiao Zhan on 12/12/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "util.h"

char** split(char*str,char*delim){
    char*sub;
    int index=0;
    char**ret;
    
    char*newstr;
    if(str==NULL)exit(EXIT_FAILURE);
    ret=malloc(256*(int)sizeof(char*));
    newstr=malloc(sizeof(char)*strlen(str));
    
    strcpy(newstr, str);
    sub=strtok(newstr,delim);
    while(sub){
        ret[index]=malloc(256*sizeof(char));
        strncpy(ret[index],sub,strlen(sub));
        index++;
        sub=strtok(NULL,delim);
    }
    return ret;
}


