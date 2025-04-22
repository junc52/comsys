#include "directory.h"
#include "inode.h"
#include "diskimg.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Looks up the specified name (name) in the specified directory (dirinumber).  
 * If found, return the directory entry in space addressed by dirEnt.  Returns 0 
 * on success and something negative on failure. 
 */
int directory_findname(struct unixfilesystem *fs, const char *name,
		       int dirinumber, struct direntv6 *dirEnt) {
  // fprintf(stderr, "directory_lookupname(name=%s dirinumber=%d)\n", name, dirinumber);
  struct inode in;
  if (inode_iget(fs, dirinumber, &in) < 0) {
    return -1;
  }
  
  if (!(in.i_mode & IALLOC) || ((in.i_mode & IFMT) != IFDIR)) {
    /* Not allocated or not a directory */
    return -1;
  }

  int size = inode_getsize(&in);
  assert((size % sizeof(struct direntv6)) == 0);

  int numBlocks  = (size + DISKIMG_SECTOR_SIZE - 1) / DISKIMG_SECTOR_SIZE;
  char buf[DISKIMG_SECTOR_SIZE];
  struct direntv6 *dir = (struct direntv6 *) buf;
  for (int bno = 0; bno < numBlocks; bno++) {
    int bytes = file_getblock(fs, dirinumber, bno, dir);
    if (bytes < 0) {
      fprintf(stderr, "Error reading directory\n");
      return -1;
    }

    int numEntriesInBlock = bytes/sizeof(struct direntv6);
    for (int i = 0; i < numEntriesInBlock; i++) {
      if (strcmp(dir[i].d_name, ".") == 0 || strcmp(dir[i].d_name, "..") == 0) {
        continue;
      }
      if (strcmp(dir[i].d_name, name) == 0) {
        *dirEnt = dir[i];
        return 0;
      }
    }
  }

  return -1;
}
