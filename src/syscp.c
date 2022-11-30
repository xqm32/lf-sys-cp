// Author: Qiming Xu
// Contact: xqm@mail.hfut.edu.cn

#include <errno.h>     // for errno
#include <fcntl.h>     // for open, creat
#include <stdint.h>    // for uint8_t
#include <stdio.h>     // for printf
#include <string.h>    // for strerror
#include <sys/stat.h>  // for S_IRUSR, S_IWUSR
#include <unistd.h>    // for read, write

#ifndef BUFFSIZE
#define BUFFSIZE 1024
#endif

int main(int argc, char *argv[]) {
    // Bad usage
    if (argc != 3) {
        printf("Usage: syscp SOURCE DEST\n");
        // See https://man.archlinux.org/man/errno.3#EINVAL
        return EINVAL;
    }
    printf("syscp[%d]: Copying...\n", BUFFSIZE);

    // See https://man.archlinux.org/man/core/man-pages/open.2.en#DESCRIPTION
    // The argument flags must include one of the following access modes:
    // O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file read-only,
    // write-only, or read/write, respectively
    int rfd = open(argv[1], O_RDONLY);
    // See https://man.archlinux.org/man/core/man-pages/open.2.en#RETURN_VALUE
    if (rfd == -1) {
        printf("syscp: %s: %s\n", argv[1], strerror(errno));
        return errno;
    }

    // See https://man.archlinux.org/man/core/man-pages/open.2.en#creat()
    // See https://man.archlinux.org/man/chmod.2.en
    int wfd = creat(argv[2], S_IRUSR | S_IWUSR);
    if (wfd == -1) {
        printf("syscp: %s: %s\n", argv[2], strerror(errno));
        return errno;
    }

    uint8_t buf[BUFFSIZE];
    ssize_t rn, wn;

    // See https://man.archlinux.org/man/read.2.en#RETURN_VALUE
    // If the file offset is at or past the end of file, no bytes are read, and
    // read() returns zero
    while ((rn = read(rfd, &buf, BUFFSIZE)) != 0) {
        if (rn == -1) {
            printf("syscp: %s, %s\n", argv[1], strerror(errno));
            return errno;
        }

        wn = write(wfd, buf, rn);
        if (wn == -1) {
            printf("syscp: %s, %s\n", argv[2], strerror(errno));
            return errno;
        }
    }

    return 0;
}