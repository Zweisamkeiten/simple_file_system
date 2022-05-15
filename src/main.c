#include <stdio.h>

#include "debug.h"

/* NODE *root, *cwd;               // root and current work directiory */
char line[128];                 // user input command line
char dname[64], bname[64];      // dirname and basename string holders

int main (int argc, char *argv[])
{
  /* initialize();     // initialize root node of the file system tree */
  while(1) {
    // get user input line = [command pathname];
    TODO();
  }
  return 0;
}
