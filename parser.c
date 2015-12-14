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

    return index;
}
