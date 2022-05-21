#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "file_system.h"
#include "utils.h"

char line[128];                   // user input command line
/* char command[16], pathname[64];   // command and pathname strings */
char dir_name[64], base_name[64]; // dirname and basename strings

fileSystem myFileSystem;

void initialize(void) {
  myFileSystem.root = new_node("/", T_DIR);
  myFileSystem.cwd = myFileSystem.root;
  // strcpy(pathname, myFileSystem.cwd->filename);
  printf(ASNI_FMT("FileSystem Initialized...\n", ASNI_FG_CYAN));
  printf(ASNI_FMT("Welcome!\n", ASNI_FG_CYAN));
}

void dbname(char *pathname) {
  char temp[128];
  strcpy(temp, pathname);
  strcpy(dir_name, dirname(temp));
  strcpy(temp, pathname);
  strcpy(base_name, basename(temp));
}

NODE *parse_pathname(char *pathname) {
  dbname(pathname);
  Debug("Debug: dirname = %s, basename = %s\n", dir_name, base_name);

  NODE *node;
  if (dir_name[0] == '/') {
    // 绝对路径 从 root 开始解析
    if (strcmp(dir_name, "/") == 0)
      node = myFileSystem.root;
    else
      node = find_node(myFileSystem.root, dir_name);
  } else {
    // 相对路径 从 cwd 开始解析
    if (strcmp(dir_name, ".") == 0) {
      node = myFileSystem.cwd;
    } else if (strcmp(dir_name, "..") == 0) {
      node = myFileSystem.cwd->parent;
    } else
      node = find_node(myFileSystem.cwd, dir_name);
  }
  return node;
}

void print_node(NODE *cur_node){
    if(cur_node->type == T_DIR){
        printf(ASNI_FMT("%s\n", ASNI_FG_BLUE), cur_node->filename);
    }
    else
    {
        printf("%s\n", cur_node->filename);
    }
}

NODE *new_node(char *name, char type) {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  Debug("Debug: Create a new NODE with name: %s\n", name);
  strcpy(node->filename, name);
  node->type = type;
  node->parent = NULL;
  node->child = NULL;
  node->sibling = NULL;
  return node;
}

void insert_node(NODE *p, char *name, char type) {
  // p is the directory to insert
  NODE *new_child = new_node(name, type);

  if (p->child == NULL) {
    // insert the node when parent is empty directory
    p->child = new_child;
    new_child->parent = p;
  } else {
    // parent has children, get the first child
    p = p->child;
    while (p->sibling != NULL) {
      // get the end of sibling children
      p = p->sibling;
    }
    p->sibling = new_child;
    new_child->parent = p->parent;
  }
}

NODE *find_node(NODE *cur_node, char *pathname) {
  char *sub_str;
  // first call strtok
  sub_str = strtok(pathname, "/");
  while (sub_str != NULL) {
    if (strcmp(sub_str, ".") == 0) {
      cur_node = myFileSystem.cwd;
    } else if (strcmp(sub_str, "..") == 0) {
      cur_node = myFileSystem.cwd->parent;
    } else
      cur_node = find_Helper(cur_node->child, sub_str, T_DIR);
    if (cur_node == NULL) {
      Debug("Debug: Find_Node failed!");
      break;
    }
    sub_str = strtok(NULL, "/");
  }
  return cur_node;
}

NODE *find_Helper(NODE *cur_node, char *target, char filetype) {
  if (cur_node == NULL) {
    printf(ASNI_FMT("Invalid path: ", ASNI_FG_RED));
    if (filetype == T_DIR) {
      printf(ASNI_FMT("Directory %s not found!\n", ASNI_FG_RED), target);
    } else {
      printf(ASNI_FMT("File %s not found!\n", ASNI_BG_RED), target);
    }
    return cur_node;
  } else if (strcmp(target, "..") == 0) {
    return cur_node->parent;
  } else if (strcmp(target, ".") == 0) {
    return cur_node;
  } else if (strcmp(target, "/") == 0) {
    return myFileSystem.root;
  } else if (strcmp(cur_node->filename, target) == 0 &&
             cur_node->type == filetype) {
    Debug("Debug: Found %s == %s\n", cur_node->filename, target);
    return cur_node;
  } else {
    Debug("Debug: Found %s != %s\n", cur_node->filename, target);
    return find_Helper(cur_node->sibling, target, filetype);
  }
}

void pwd_Helper(NODE *cur_node) {
  if (cur_node->filename == myFileSystem.root->filename) {
    printf("/");
    return;
  }
  pwd_Helper(cur_node->parent);
  if (cur_node->parent == myFileSystem.root) {
    printf("%s", cur_node->filename);
  } else {
    printf("/%s", cur_node->filename);
  }
}
