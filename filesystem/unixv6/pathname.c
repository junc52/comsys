
#include "pathname.h"
#include "directory.h"
#include "inode.h"
#include "diskimg.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int pathname_lookup(struct unixfilesystem *fs, const char *pathname) {
  // remove the placeholder implementation and replace with your own
  // fprintf(stderr, "pathname_lookup(path=%s) unimplemented.  Returing -1.\n", pathname);
  if (pathname == NULL || pathname[0] != '/') {
    return -1;
  }

  if (strcmp(pathname, "/") == 0) {
    return ROOT_INUMBER; // special base case
  }

  char pathname_copy[1024];
  strncpy(pathname_copy, pathname, sizeof(pathname_copy));
  pathname_copy[sizeof(pathname_copy) - 1] = '\0';
  
  char *token = strtok(pathname_copy, "/");
  int current_inumber = ROOT_INUMBER;

  while(token != NULL) {
    struct direntv6 entry;
    if (directory_findname(fs, token, current_inumber, &entry) < 0) {
      return -1;
    }

    current_inumber = entry.d_inumber;
    token = strtok(NULL, "/");
  }

  return current_inumber;
}
