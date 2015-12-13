//
//  util.c
//  sish
//
//  Created by Yanqiao Zhan on 12/12/15.
//  Copyright © 2015 Yanqiao Zhan. All rights reserved.
//

#include "util.h"

char** split(char*str,char*delim){
    char*sub=strtok(str,delim);
    int index=0;
    char**ret=malloc(256*sizeof(char*));
    while(sub){
        ret[index]=malloc(256*sizeof(char));
        strncpy(ret[index],sub,strlen(sub));
        index++;
        sub=strtok(NULL,delim);
    }
    return ret;
}