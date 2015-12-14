/*
  define.h
  sish

  Created by Yanqiao Zhan on 12/12/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#ifndef define_h
#define define_h

typedef struct command{
    char*argv;
    int flag_a;/*append standard output*/
    int flag_o;/*redirect standard output*/
    int flag_i;/*redirect standard input*/
    char*infilepath;/*redirection input(<)*/
    char*outfilepath;/*redirection output(>)*/
    char*appendfilepath;/*append output(>>)*/
}Command;

typedef struct argument{
    int flag_c;
    int flag_x;
    int flag_d;/*if a command is terminated by &, the shell execute daemond*/
    char*rawcommand;
}Arg;

extern int exit_code;
#endif /* define_h */
