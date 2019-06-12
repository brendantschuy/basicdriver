#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>    
#include <string.h>

#define MAX_LEN 80

int main(int argc, char ** argv) {
    char byte;
    char insertString[MAX_LEN];
    if(argc == 1)
    {
	    printf("Usage: <writer> <string>\n");
	    return(-1);
    }
    if(argc == 2)
    {
	    strcpy(insertString, argv[1]);
    }
    //strcpy(insertString, "PROG");
    int fd = open("/dev/533driver", O_RDWR | O_APPEND);

    int n = strlen(insertString);

    write(fd, insertString, n - 1);

    ssize_t size = read(fd, &byte, 1);
    printf("Read byte %c\n", byte);

    if(close(fd) < 0)
    {
	    return 1;
    }
    return 0;
}
