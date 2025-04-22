#include <stdio.h>
#include <assert.h>

#include "file.h"
#include "inode.h"
#include "diskimg.h"

// remove the placeholder implementation and replace with your own
int file_getblock(struct unixfilesystem *fs, int inumber, int blockNum, void *buf) {
  // fprintf(stderr, "file_getblock(inumber = %d, blockNum = %d) unimplemented. returning -1\n", inumber, blockNum);
  if (inumber < 0 || (size_t)inumber >= fs->num_inodes) {
    fprintf(stderr, "Invalid inode number %d\n", inumber);
  }

  struct inode in;
  int err = inode_iget(fs, inumber, &in);
  if (err < 0) {
    return err;
  }

  int filesize = inode_getsize(&in);
  if (filesize > DISKIMG_SECTOR_SIZE * 8) {
    fprintf(stderr, "Inode %d : Invalid file size\n", inumber);
    return -1;
  }

  int offset = blockNum * DISKIMG_SECTOR_SIZE;
  int diskBlockNum = inode_indexlookup(fs, &in, blockNum);
  if (diskBlockNum < 0) {
    return -1;
  }

  int readbytes = diskimg_readsector(fs->dfd, diskBlockNum, buf);
  if (readbytes < 0) {
    fprintf(stderr, "Inode %d : Failed to read block\n", diskBlockNum);
    return -1;
  }

  int valid_bytes = filesize - offset;
  if (valid_bytes > DISKIMG_SECTOR_SIZE) {
    valid_bytes = DISKIMG_SECTOR_SIZE;
  }
  return valid_bytes;  
}
