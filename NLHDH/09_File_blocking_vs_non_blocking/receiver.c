#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int
main(argc, argv)
int argc;
char    *argv[];
{
    char    s[80], *t = "Receive: ";
    char    *file;
    int block;
    int fd; 
    FILE    *fs;
    
    if (argc != 3) {
        printf("Usage: %s filename blocking_mode (0, 1)\n", argv[0]);
        return(-1);
    }
    file = argv[1];
    block = atoi(argv[2]);
    if (block == 1) {
        printf("Blocking mode\n");
        fd = open(file, O_RDONLY & ~O_NONBLOCK);    // Blocking mode
    }
    else {
        printf("Non-blocking mode\n");
        fd = open(file, O_RDONLY | O_NONBLOCK);     // Non-blocking mode
    }
    
    if (fd < 0) {
        perror("Cannot open file");
        return(1);
    }
    else fs = fdopen(fd, "r");
    
    while (fgets(s, 79, fs) != NULL) {
        write(1, t, strlen(t));
        write(1, s, strlen(s));
    }
    close(fd);
    return(0);
}

 