#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int
main(argc, argv)
int argc;
char    *argv[];
{
    char    s[80], *t = "Send: ";
    char    *file;
    int block;
    int fd;

    if (argc != 3) {
        printf("Usage: %s filename blocking_mode (0, 1)\n", argv[0]);
        return(-1);
    }
    file = argv[1];
    block = atoi(argv[2]);
    if (block == 1) {
        printf("Blocking mode\n");
        fd = open(file, O_WRONLY & ~O_NONBLOCK);    // Blocking mode
    }
    else {
        printf("Non-blocking mode\n");
        fd = open(file, O_WRONLY | O_NONBLOCK);     // Non-blocking mode
    }

    if (fd < 0) {
        perror("Cannot open file");
        return(1);
    }
    while (fgets(s, 79, stdin) != NULL) {
        // write(fd, t, strlen(t));
        write(fd, s, strlen(s));
    }
    close(fd);
    return(0);
}