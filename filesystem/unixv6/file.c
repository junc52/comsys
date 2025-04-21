#include <stdio.h>
#include <assert.h>

#include "file.h"
#include "inode.h"
#include "diskimg.h"

// remove the placeholder implementation and replace with your own
int file_getblock(struct unixfilesystem *fs, int inumber, int blockNum, void *buf) {
  // fprintf(stderr, "file_getblock(inumber = %d, blockNum = %d) unimplemented. returning -1\n", inumber, blockNum);
  if (inumber < 0 || inumber >= fs->num_inodes) {
    fprintf(stderr, "Invalid inode number %d\n", inumber);
  }

  struct inode in;
  int err = inode_iget(fs, inumber, &in);
  if (err < 0) {
    return err;
  }
  // TODO : check the type of diskBlockNum
  int diskBlockNum = inode_indexlookup(fs, &in, blockNum);
  if (diskBlockNum < 0) {
    return -1;
  }

  int readbytes = diskimg_readsector(fs->dfd, diskBlockNum, buf);
  return readbytes;  
}
