#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "inode.h"
#include "diskimg.h"

// remove the placeholder implementation and replace with your own
int inode_iget(struct unixfilesystem *fs, int inumber, struct inode *inp) {
  if (inumber < 0 || inumber >= fs->num_inodes) {
    fprintf(stderr, "Invalid inode number %d\n", inumber);
  }

  if (fs->inode_table == NULL) {
    fs->inode_table = malloc(fs->num_inodes * sizeof(struct inode));
    if (fs->inode_table == NULL) {
      fprintf(stderr, "Error malloc failed\n");
      return -1;
    }

    for (int i = 0; i < fs->superblock.s_isize; i++) {
      void *buf = (void *)((uint8_t *)(fs->inode_table) + DISKIMG_SECTOR_SIZE * i);
      if (diskimg_readsector(fs->dfd, INODE_START_SECTOR + i, buf) != DISKIMG_SECTOR_SIZE) {
        fprintf(stderr, "Error reading inode block %d\n", INODE_START_SECTOR + i);
        free(fs->inode_table);
        fs->inode_table = NULL;
        return -1;
      }
    }
  }

  *inp = fs->inode_table[inumber - 1];
  return 0;  
}

// remove the placeholder implementation and replace with your own
int inode_indexlookup(struct unixfilesystem *fs, struct inode *inp, int blockNum) {
  if (blockNum < 0 || blockNum >= 8) {
    fprintf(stderr, "Invalid block number %d\n", blockNum);
    return -1;
  }

  if (inp == NULL) {
    fprintf(stderr, "Invalid inode to lookup\n");
    return -1;
  }

  // TODO : check the type of diskBlockNum
  uint16_t diskBlockNum = inp->i_addr[blockNum];
  if (diskBlockNum == 0) {
    fprintf(stderr, "Block not allocated\n");
    return -1;
  }

  return diskBlockNum;
}

int inode_getsize(struct inode *inp) {
  return ((inp->i_size0 << 16) | inp->i_size1); 
}
