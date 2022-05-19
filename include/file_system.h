#ifndef file_system_h
#define file_system_h

typedef struct node {
  char filename[64];    // Name of file
  enum { D, F } type;   // File type : File or Directory
  struct node *parent;  // Pointer to parent directory
  struct node *sibling; // Pointer to sibling file
  struct node *child;   // Pointer to child file
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

#endif
