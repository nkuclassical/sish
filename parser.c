/*
 parser.c
 sish
 
 Created by Yanqiao Zhan on 12/12/15.
 Copyright © 2015 Yanqiao Zhan. All rights reserved.
 */

#include "parser.h"
int empty(char*str){
    int index=0;
    for(index=0;index<strlen(str);index++){
        if(str[index]!=' ')return 0;
    }
    return 1;
}

int parserdirection(Command *command){
    int index=0;
    int redirectoutputnum=0;
    int appendnum=0;
    int redirectinputnum=0;
    int redirectoutputstart=0;
    int appendstart=0;
    int redirectinputstart=0;
    int len;
    int arglength=(int)strlen(command->argv);
    char*newcommandcontent;
    command->flag_a=0;
    command->flag_i=0;
    command->flag_o=0;
    for (index=0; index<strlen(command->argv); index++) {
        if (command->argv[index]=='<') {
            redirectinputnum++;
            redirectinputstart=index;
            if(index<arglength)arglength=index-1;
        }else if(command->argv[index]=='>'){
            if(index==strlen(command->argv)-1)return -1;
            if(index<arglength)arglength=index-1;
            if(command->argv[index+1]=='>'){
                appendnum++;
                index++;
                appendstart=index;
            }else{
                redirectoutputnum++;
                redirectoutputstart=index;
            }
        }
    }
    if(redirectinputnum>1||redirectoutputnum>1||appendnum>1){
        return -1;
    }
    
    if(redirectoutputnum==1){
        for(index=redirectoutputstart+1;index<strlen(command->argv);index++){
            if(command->argv[index]!=' '){
                redirectoutputstart=index;
                break;
            }
        }
        if(index==strlen(command->argv))return -1;
        while (index<strlen(command->argv)) {
            if(command->argv[index]==' '||command->argv[index]=='>'||command->argv[index]=='<'){
                break;
            }
            index++;
        }
        len=index-redirectoutputstart;
        command->outfilepath=malloc(sizeof(char)*(len+1));
        memcpy(command->outfilepath, &(command->argv[redirectoutputstart]), len);
        command->outfilepath[len]='\0';
        command->flag_o=1;
        command->flag_a=0;
        
    }
    
    if(redirectinputnum==1){
        for(index=redirectinputstart+1;index<strlen(command->argv);index++){
            if(command->argv[index]!=' '){
                redirectinputstart=index;
                break;
            }
        }
        if(index==strlen(command->argv))return -1;
        while (index<strlen(command->argv)) {
            if(command->argv[index]==' '||command->argv[index]=='>'||command->argv[index]=='<'){
                break;
            }
            index++;
        }
        len=index-redirectinputstart;
        command->infilepath=malloc(sizeof(char)*(len+1));
        memcpy(command->infilepath, &(command->argv[redirectinputstart]), len);
        command->infilepath[len]='\0';
        command->flag_i=1;
    }
    
    if(appendnum==1){
        for(index=appendstart+1;index<strlen(command->argv);index++){
            if(command->argv[index]!=' '){
                appendstart=index;
                break;
            }
        }
        if(index==strlen(command->argv))return -1;
        while (index<strlen(command->argv)) {
            if(command->argv[index]==' '||command->argv[index]=='>'||command->argv[index]=='<'){
                break;
            }
            index++;
        }
        len=index-appendstart;
        command->appendfilepath=malloc(sizeof(char)*(len+1));
        memcpy(command->appendfilepath, &(command->argv[appendstart]), len);
        command->appendfilepath[len]='\0';
        if(command->flag_o==1&&appendstart>redirectoutputstart){ /*only if >> appears after >, then >> will be efficient*/
            command->flag_a=1;
            command->flag_o=0;
        }
    }
    newcommandcontent=malloc(sizeof(char)*(arglength+1));
    strncpy(newcommandcontent, command->argv, arglength);
    newcommandcontent[arglength]='\0';
    strcpy(command->argv, newcommandcontent);

    return 0;
}


int parser(char*rawcommand,Command allcommands[],Arg*arg){
    char**subcommands;
    int index=0;
    int i=0,len;
    char *pch;
    len=(int)strlen(rawcommand);
    if(rawcommand[len-1]=='|')return -1;
    subcommands=split(rawcommand, "|");
    while(subcommands[index]){
        allcommands[index].argv=malloc(sizeof(char)*(strlen(subcommands[index])+1));
        strcpy(allcommands[index].argv, subcommands[index]);
        allcommands[index].argv[strlen(subcommands[index])]='\0';
        index++;
    }
    
    for(i=0;i<index-1;i++){
        pch=strchr(allcommands[i].argv, '&');
        if(pch!=NULL)return -1;/* & can only occur at the end of command*/
        if (strcmp(allcommands[i].argv, "exit")==0) {
            if(i>0){
                return -1;
            }
        }
    }
    if(strcmp(allcommands[index-1].argv, "exit")==0){
        if(index==1){
            return 0;
        }
        return -1;
    }
    if(empty(allcommands[i].argv)==1)return -1;
    pch=strchr(allcommands[i].argv, '&');
    if(pch!=NULL){
        if(pch-allcommands[i].argv+1==strlen(allcommands[i].argv)){
            arg->flag_d=1;
            len=(int)strlen(allcommands[i].argv);
            allcommands[i].argv[len-1]='\0';
        }else{
            return -1;
        }
    }
    
    for(i=0;i<index;i++){
        if(parserdirection(&allcommands[i])==-1)return -1;
    }
    
    for(i=0;i<index;i++){
        printf("output:%s!   appendfile:%s!  inputfile%s!\n",allcommands[i].outfilepath,allcommands[i].appendfilepath,allcommands[i].infilepath);
    }
    
    return index;
}
