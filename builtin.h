/*
  builtin.h
  sish

  Created by Yanqiao Zhan on 12/10/15.
  Copyright © 2015 Yanqiao Zhan. All rights reserved.
*/

#ifndef builtin_h
#define builtin_h

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "define.h"
#include "util.h"
int cdCommand(char*);
int echoCommand(char*);
#endif /* builtin_h */
