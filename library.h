#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "pwd.h"
#include "stdlib.h"
#include "string.h"
#include "sys/utsname.h"
#include "signal.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "fcntl.h"
#include <sys/stat.h>
#include <dirent.h>
#include "time.h"
#include "grp.h"



//some interfile variables
pid_t CURR_FOREGROUND;
char * CURR_FOREGROUND_NAME;


