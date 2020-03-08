#include "library.h"
#include "functions.h"
const int MAX_CMD = 16;

int argCount(char ** args)
{
    int count; 
    count=0;
    while(args[count++]);
    count--;
    return count;
}
