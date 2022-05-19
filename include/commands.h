#ifndef commands_h
#define commands_h

#include "utils.h"

extern int mkdir(char *args);
extern int rmdir(char *args);
extern int ls(char *args);
extern int cd(char *args);
extern int pwd();
extern int create(char *args);
extern int rm(char *args);
extern int load();
extern int save();
extern int menu();
extern int quit();

struct CMD_STRUCT {
  const char *name;
  const char *description;
  int (*handler)(char *);
};

#endif
