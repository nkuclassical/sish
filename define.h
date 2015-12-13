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
}Command;

typedef struct argument{
    int flag_c;
    int flag_x;
    int flag_d;/*if a command is terminated by &, the shell execute daemond*/
    char*rawcommand;
}Arg;
#endif /* define_h */
