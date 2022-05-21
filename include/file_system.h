#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

typedef struct node {
  char filename[64];                       // Name of file
  enum { T_DIR = 'D', T_FILE = 'F' } type; // File type : File or Directory
  struct node *parent;                     // Pointer to parent directory
  struct node *sibling;                    // Pointer to sibling file
  struct node *child;                      // Pointer to child file
} NODE;

/*
 * '/' as root, "cwd" as current work directory
 * Example:
 * pathname = "/path/to/file"
 * dirname = "/path/to"
 * basename = "file"
 */
typedef struct {
  NODE *root, *cwd;
} fileSystem;

extern char line[];                // user input command line
/* extern char command[], pathname[]; // command and pathname strings */
extern char dir_name[], base_name[]; // dirname and basename strings

extern void print_node(NODE *cur_node);
extern NODE *new_node(char *name, char type);
extern void insert_node(NODE *parent, char *name, char type);
extern NODE *find_node(NODE *cur_node, char *pathname);
extern NODE *find_Helper(NODE *cur_node, char *target, char filetype);
extern void pwd_Helper(NODE *cur_node);
extern void initialize(void);
extern void dbname(char *pathname);
extern NODE *parse_pathname(char *pathname);

extern fileSystem myFileSystem;

#endif
