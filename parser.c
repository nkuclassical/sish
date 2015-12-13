/*
  parser.c
  sish

  Created by Yanqiao Zhan on 12/12/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#include "parser.h"
int parser(char*rawcommand,Command allcommands[]){
    char**subcommands=split(rawcommand, "|");
    int index=0;
    while(subcommands[index]){
        allcommands[index].argv=malloc(sizeof(char)*(strlen(subcommands[index])+1));
        strcpy(allcommands[index].argv, subcommands[index]);
        allcommands[index].argv[strlen(subcommands[index])]='\0';
        index++;
    }
    return index;
}
