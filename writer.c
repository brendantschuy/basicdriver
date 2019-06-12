#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>    
#include <string.h>

#define MAX_LEN 20

int main() {
    char byte;
    char insertString[MAX_LEN];
    strcpy(insertString, "Barnacles");
    int fd = open("/dev/fake123", O_RDWR | O_APPEND);

    int n = strlen(insertString);

    write(fd, insertString, n - 1);
    write(fd, insertString, n - 1);
    ssize_t size = read(fd, &byte, 1);
    printf("Read byte %c\n", byte);

    if(close(fd) < 0)
    {
	    return 1;
    }
    return 0;
}
