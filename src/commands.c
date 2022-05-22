#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "debug.h"
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
  char *arg = strtok(NULL, " ");

  if (args == NULL) {
    printf(ASNI_FMT("mkdir: missing operand\n", ASNI_FG_RED));
  } else {
    if (arg == NULL) arg = args;
    dbname(arg);
    NODE *location = parse_pathname(arg);
    if (location == NULL) {
      printf(ASNI_FMT("mkdir: cannot create directory '%s': No such file or "
                      "directory\n",
                      ASNI_FG_RED),
             arg);
      return 1;
    }
    NODE *dupe_serach = location->child;
    while (dupe_serach != NULL) {
      if (strcmp(dupe_serach->filename, base_name) == 0 &&
          dupe_serach->type == T_DIR) {
        printf(ASNI_FMT("mkdir: cannot create directory '%s': File exists\n",
                        ASNI_FG_RED),
               arg);
        return 1;
      }
      dupe_serach = dupe_serach->sibling;
    }
    insert_node(location, base_name, T_DIR);
  }
  return 0;
}

int rmdir(char *args) {
  char *arg = strtok(NULL, " ");

  if (args == NULL) {
    printf(ASNI_FMT("rmdir: missing operand\n", ASNI_FG_RED));
  } else {
    dbname(arg);
    NODE *location = parse_pathname(arg);
    if (strcmp(base_name, ".") == 0) {
      printf(ASNI_FMT("rmdir: failed to remove '.': Invalid argument\n",
                      ASNI_FG_RED));
      return 1;
    }
    location = find_Helper(location->child, base_name, T_DIR);
    if (location->type != T_DIR) {
      printf(ASNI_FMT("rmidr: cannot remove '%s': Is a file\n", ASNI_FG_RED),
             arg);
    }
    delete_node(location);
  }
  return 0;
}

int ls(char *args) {
  char *arg = strtok(NULL, " ");

  NODE *node;

  if (args == NULL) {
    node = myFileSystem.cwd;
  } else {
    dbname(arg);
    node = parse_pathname(arg);
    if (node->child != NULL)
      node = find_Helper(node->child, base_name, T_DIR);
    else
      node = find_Helper(node, base_name, T_DIR);
  }

  if (arg != NULL && strcmp(base_name, ".") == 0) {
    if (node == myFileSystem.root) {
      node = node->child;
    }
  } else if (arg != NULL && strcmp(base_name, "..") == 0) {
    if (node == myFileSystem.root) {
      node = node->child;
    } else {
      node = node->parent;
      node = node->child;
    }
  } else {
    node = node->child;
  }
  while (node != NULL) {
    print_node(node);
    node = node->sibling;
  }
  return 0;
}

int cd(char *args) {
  char *path = strtok(NULL, " ");
  NODE *node;
  dbname(path);
  if (path != NULL) {
    dbname(path);
    node = parse_pathname(path);
    if (strcmp(base_name, "..") == 0) {
      if (node->parent != NULL) {
        node = node->parent;
      }
    } else if (strcmp(base_name, ".") == 0) {
    } else if (strcmp(base_name, "/") == 0) {
      node = myFileSystem.root;
    } else {
      node = find_Helper(node->child, base_name, T_DIR);
    }
  } else {
    node = myFileSystem.root;
  }

  if (node == NULL) {
    printf(ASNI_FMT("cd: no such file or directory: %s\n", ASNI_FG_RED), path);
    return 1;
  }

  myFileSystem.cwd = node;

  return 0;
}

int pwd() {
  pwd_Helper(myFileSystem.cwd);
  printf("\n");
  return 0;
}

int create(char *args) {
  char *arg = strtok(NULL, " ");

  if (args == NULL) {
    printf(ASNI_FMT("create: missing operand\n", ASNI_FG_RED));
  } else {
    if (arg == NULL) arg = args;
    dbname(arg);
    NODE *location = parse_pathname(arg);
    if (location == NULL) {
      printf(ASNI_FMT(
                 "create: cannot create file '%s': No such file or directory\n",
                 ASNI_FG_RED),
             arg);
      return 1;
    }
    NODE *dupe_serach = location->child;
    while (dupe_serach != NULL) {
      if (strcmp(dupe_serach->filename, base_name) == 0 &&
          dupe_serach->type == T_FILE) {
        printf(ASNI_FMT("create: cannot create file '%s': File exists\n",
                        ASNI_FG_RED),
               arg);
        return -1;
      }
      dupe_serach = dupe_serach->sibling;
    }
    insert_node(location, base_name, T_FILE);
  }
  return 0;
}

int rm(char *args) {
  char *arg = strtok(NULL, " ");

  if (args == NULL) {
    printf(ASNI_FMT("rm: missing operand\n", ASNI_FG_RED));
  } else {
    dbname(arg);
    NODE *location = parse_pathname(arg);
    if (strcmp(base_name, ".") == 0) {
      printf(ASNI_FMT("Please provide a valid filename\n", ASNI_FG_RED));
      return 1;
    }
    location = find_Helper(location->child, base_name, T_FILE);
    if (location == NULL) {
      printf(ASNI_FMT("rm: cannot remove '%s': No such file\n", ASNI_FG_RED),
             arg);
      return 1;
    }
    if (location->type != T_FILE) {
      printf(ASNI_FMT("rm: cannot remove '%s': Is a directory", ASNI_FG_RED),
             arg);
      return 1;
    }

    delete_node(location);
  }
  return 0;
}

int load(char *args) {
  char *arg = strtok(NULL, " ");
  char filename[64];

  if (args == NULL) {
    /* no argument given */
    strcpy(filename, "myfilesystem.txt");
  } else {
    strcpy(filename, arg);
  }

  char buf[128], type, path[128];

  FILE *fp = fopen(filename, "r");
  fgets(buf, 128, fp);
  fgets(buf, 128, fp);
  fgets(buf, 128, fp);

  while (fgets(buf, 128, fp)) {
    buf[strlen(buf) - 1] = '\0';
    sscanf(buf, "%c\t%s", &type, path);

    Debug("load %c\t%s\n", type, path);

    switch (type) {
    case 'D':
      mkdir(path);
      break;
    case 'F':
      create(path);
      break;
    default:
      printf(ASNI_FMT("Loading file '%s' failed\n", ASNI_FG_RED), path);
    }
  }

  printf(ASNI_FMT("Filesystem is loaded by file '%s' successfully\n",
                  ASNI_FG_CYAN),
         filename);
  fclose(fp);

  return 0;
}

int save(char *args) {
  char *arg = strtok(NULL, " ");
  char filename[64];

  if (args == NULL) {
    /* no argument given */
    strcpy(filename, "myfilesystem.txt");
  } else {
    strcpy(filename, arg);
  }

  Debug(ASNI_FMT("Saving current filesystem to %s\n", ASNI_FG_YELLOW),
        filename);

  FILE *fp = fopen(filename, "w+");
  fprintf(fp, "type\tfilename\n\n");
  recursive_print(myFileSystem.root, fp);

  fclose(fp);

  Debug(ASNI_FMT("Saved.\n", ASNI_FG_YELLOW));

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
