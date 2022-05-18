#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "utils.h"

#define DIRECTORY_TYPE 'D'
#define FILE_TYPE 'F'

static int mkdir(char *args);
static int rmdir(char *args);
static int ls(char *args);
static int cd(char *args);
static int pwd();
static int create(char *args);
static int rm(char *args);
static int load();
static int save();
static int menu();
static int quit();

struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table[] = {
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

#define CMD_NUM ARRLEN(cmd_table)

typedef struct node {
  char *filename[64];
  char type;
  struct node *parent;
  struct node *sibling;
  struct node *child;
} NODE;

/*
 * '/' as root, "cwd" as current work directory
 * Example:
 * pathname = "/path/to/file"
 * dirname = "/path/to"
 * basename = "file"
 */
NODE *root, *cwd;
char line[128];                 // user input command line
char command[16], pathname[64]; // command and pathname strings
char dirname[64], basename[64]; // dirname and basename strings

// void initialize(void);

static char *rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline(ASNI_FMT("User@machine: ", ASNI_FG_RED));

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

int main(int argc, char *argv[]) {
  /* initialize();     // initialize root node of the file system tree */

  for (char *str; (str = rl_gets()) != NULL;) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

    // identify the command;
    // execute the command;
    for (int i = 0; i < CMD_NUM; i++) {
      // found command: return index i
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) {
          return 0;
        }
        break;
      }
      if (i == CMD_NUM) {
        printf("Unknown command '%s'\n", cmd);
      }
    }
  }
}

static int mkdir(char *args) {
  printf("mkdir\n");
  return 0;
}

static int rmdir(char *args) {
  printf("rmdir\n");
  return 0;
}

static int ls(char *args) {
  printf("ls\n");
  return 0;
}

static int cd(char *args) {
  printf("cd\n");
  return 0;
}

static int pwd() {
  printf("pwd\n");
  return 0;
}

static int create(char *args) {
  printf("create\n");
  return 0;
}

static int rm(char *args) {
  printf("rm\n");
  return 0;
}

static int load() {
  printf("load\n");
  return 0;
}

static int save() {
  printf("save\n");
  return 0;
}

static int menu() {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < CMD_NUM; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < CMD_NUM; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int quit() {
  printf("quit\n");
  return -1;
}
