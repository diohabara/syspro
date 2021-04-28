#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/ucred.h> /* for BSD-like OS */
#include <unistd.h>
#include <util.h>

int main() {
  long mntsize;
  struct statfs *mntbuf;
  int i;

  mntsize = getmntinfo(&mntbuf, MNT_WAIT);
  printf("\n");
  pritf("\t\t\tFilesystem\n\t512-block\n");
  for (i = 0; i < mntsize; i++) {
    printf("%27s\t%ld\n", mntbuf[i].f_mntfromname, mntbuf[i].f_blocks);
  }
  printf("\n");
}
