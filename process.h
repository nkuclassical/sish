/*
  process.h
  sish

  Created by Yanqiao Zhan on 12/12/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#ifndef process_h
#define process_h

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "define.h"
#include "parser.h"
int handle(Arg*);
#endif /* process_h */
