#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

int main() {
    int fd = open("/dev/eudyptula", O_RDWR);
    assert(fd > 0);

    char *buf = (char *)malloc(4);
    int nbytes = read(fd, buf, 4);

    printf("read %d bytes \n", nbytes);
    assert(nbytes == 4);

    printf("read %s string\n", buf);
    assert(strcmp("n2h9", buf) == 0);

    printf("ok read \n");

    char *bufw = "some_string";
    int nbytesw = write(fd, bufw, strlen(bufw));
    
    printf("wrote %d bytes \n", nbytesw);
    assert(nbytesw == -1);

    bufw = "n2h9";
    nbytesw = write(fd, bufw, strlen(bufw));
    
    printf("wrote %d bytes \n", nbytesw);
    assert(nbytesw == 4);

    printf("ok write\n");

    free(buf);
    close(fd);
    printf("all done\n");
    return 0;
}