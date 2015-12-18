/*
 util.c
 sish
 
 Created by Yanqiao Zhan on 12/12/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "util.h"

int exit_code;
void *Malloc(size_t size){
    void*ret=malloc(size);
    if(ret==NULL){
        exit_code=1;
        exit(1);
    }
    return ret;
}
char** split(char*str,char*delim){
    char*sub;
    int index=0;
    char**ret;
    char*temp;
    char*newstr;
    if(str==NULL)exit(EXIT_FAILURE);
    ret=Malloc(256*(int)sizeof(char*));
    newstr=Malloc(sizeof(char)*strlen(str));
    strcpy(newstr, str);
    sub=strtok(newstr,delim);
    while(sub){
        temp=trim(sub);
        ret[index]=Malloc(256*sizeof(char));
        strncpy(ret[index],temp,strlen(temp));
        index++;
        sub=strtok(NULL,delim);
    }
    return ret;
}

char*trim(char*str){
    int startindex=0;
    int endindex=(int)strlen(str);
    int i=0;
    char *retstr;
    for(i=0;i<strlen(str);i++){
        if(str[i]!=' ')break;
    }
    startindex=i;
    for(i=(int)strlen(str)-1;i>startindex;i--){
        if(str[i]!=' ')break;
    }
    endindex=i;
    retstr=Malloc(sizeof(char)*(endindex-startindex+2));
    memcpy(retstr, &str[startindex], endindex-startindex+1);
    retstr[endindex-startindex+1]='\0';
    return retstr;
}

