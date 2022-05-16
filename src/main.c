#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "utils.h"

char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "touch", "rm", "reload", "save", "menu", "quit", NULL};

static int findCmd(char *command);
static int mkdir(char *args);
static int rmdir(char *args);
static int ls(char *args);
static int cd(char *args);
static int pwd();
static int touch(char *args);
static int rm(char *args);
static int reload();
static int save();
static int menu();
static int quit();

int main (int argc, char *argv[])
{
  int index;
  char line[128], command[16], pathname[64];
  /* initialize();     // initialize root node of the file system tree */
  while(1) {
    // get user input line = [command pathname];
    printf(ASNI_FMT("User@machine:", ASNI_FG_RED));
    fgets(line, 128, stdin);
    line[strlen(line) - 1] = 0;
    sscanf(line, "%s %s", command, pathname);
    index = findCmd(command);
    switch(index)
    {
      case 0: mkdir(pathname);  break;
      case 1: rmdir(pathname);  break;
      case 2: ls(pathname);     break;
      case 3: cd(pathname);     break;
      case 4: pwd();            break;
      case 5: touch(pathname);  break;
      case 6: rm(pathname);     break;
      case 7: reload();         break;
      case 8: save();           break;
      case 9: menu();           break;
      case 10: quit();          break;
      default:
        printf("invalid command %s\n", command);
    }
  }
  return 0;
}

int findCmd(char *command)
{
  int i = 0;
  while(cmd[i]) {
    // found command: return index i
    if (!strcmp(command, cmd[i]))
      return i;
    i++;
  }

  // not found: return -1
  return -1;
}

static int mkdir(char *args)
{
  printf("mkdir\n");
  return 1;
}

static int rmdir(char *args)
{
  printf("rmdir\n");
  return 1;
}

static int ls(char *args)
{
  printf("ls\n");
  return 1;
}

static int cd(char *args)
{
  printf("cd\n");
  return 1;
}

static int pwd()
{
  printf("pwd\n");
  return 1;
}

static int touch(char *args)
{
  printf("touch\n");
  return 1;
}

static int rm(char *args)
{
  printf("rm\n");
  return 1;
}

static int reload()
{
  printf("reload\n");
  return 1;
}

static int save()
{
  printf("save\n");
  return 1;
}

static int menu()
{
  printf("menu\n");
  return 1;
}

static int quit()
{
  printf("quit\n");
  return -1;
}
