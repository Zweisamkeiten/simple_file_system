#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "debug.h"
#include "file_system.h"
#include "utils.h"

extern struct CMD_STRUCT cmd_table[];
extern int CMD_NUM; // The number of commands

bool debug = true; // 启用 Debug

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
  initialize(); // initialize root node of the file system tree

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
