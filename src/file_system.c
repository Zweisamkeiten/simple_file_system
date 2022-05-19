#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "file_system.h"

char line[128];                 // user input command line
char command[16], pathname[64]; // command and pathname strings
char dirname[64], basename[64]; // dirname and basename strings

fileSystem myFileSystem;

void initialize(void) {
  myFileSystem.root = new_node("/", T_DIR);
  myFileSystem.cwd = myFileSystem.root;
  strcpy(pathname, myFileSystem.cwd->filename);
  printf("Initialized OK...\n");
}

NODE *new_node(char *name, char type) {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  Debug("Create a new NODE with name: %s\n", name);
  strcpy(node->filename, name);
  node->type = type;
  node->parent = NULL;
  node->child = NULL;
  node->sibling = NULL;
  return node;
}
