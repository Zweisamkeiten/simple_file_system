#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "file_system.h"
#include "utils.h"

struct CMD_STRUCT cmd_table[] = {
    {"mkdir", "Make directories", mkdir},
    {"rmdir", "Remove directories", rmdir},
    {"ls", "List directory contents", ls},
    {"cd", "Change the working directory", cd},
    {"pwd", "Print name of current/working directory", pwd},
    {"create", "Create a new file", create},
    {"rm", "Remove files", rm},
    {"load", "Load a file to create the file system", load},
    {"save", "Save the current file system to a file", save},
    {"menu", "Print all commands with its description", menu},
    {"quit", "Quit the file system", quit},
};

#define NM_CMD ARRLEN(cmd_table)
int CMD_NUM = NM_CMD;

int mkdir(char *args) {
  printf("mkdir\n");
  return 0;
}

int rmdir(char *args) {
  printf("rmdir\n");
  return 0;
}

int ls(char *args) {
  printf("ls\n");
  return 0;
}

int cd(char *args) {
  printf("cd\n");
  return 0;
}

int pwd() {
  pwd_Helper(myFileSystem.cwd);
  printf("\n");
  return 0;
}

int create(char *args) {
  printf("create\n");
  return 0;
}

int rm(char *args) {
  printf("rm\n");
  return 0;
}

int load() {
  printf("load\n");
  return 0;
}

int save() {
  printf("save\n");
  return 0;
}

int menu() {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < CMD_NUM; i++) {
      printf(ASNI_FMT("%s", ASNI_FG_GREEN), cmd_table[i].name);
      printf(ASNI_FMT(" - ", ASNI_FG_YELLOW));
      printf(ASNI_FMT("%s\n", ASNI_FG_BLUE), cmd_table[i].description);
    }
  } else {
    for (i = 0; i < CMD_NUM; i++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf(ASNI_FMT("%s", ASNI_FG_GREEN), cmd_table[i].name);
        printf(ASNI_FMT(" - ", ASNI_FG_YELLOW));
        printf(ASNI_FMT("%s\n", ASNI_FG_BLUE), cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

int quit() {
  printf("quit\n");
  return -1;
}
