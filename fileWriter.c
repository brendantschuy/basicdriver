#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>    
#include <string.h>

#define MAX_LEN 80

int main(int argc, char ** argv) {
    char byte;
    int c;
    char fileName[MAX_LEN];
    char fileContents[MAX_LEN];
    if(argc == 1)
    {
	    printf("Usage: <writer> <string>\n");
	    return(-1);
    }
    if(argc == 2)
    {
	    strcpy(fileName, argv[1]);
    }
    FILE * file;
    file = fopen(fileName, "r");
    int i = 0;
    if(file)
    {
	    while((c = getc(file)) != EOF)
	    {
		    fileContents[i] = c;
		    i++;
	    }
	    fclose(file);
    }
    printf("string: %s\n", fileContents);
    
    int fd = open("/dev/533final", O_RDWR | O_APPEND);

    int n = strlen(fileContents);

    write(fd, fileContents, n - 1);

    ssize_t size = read(fd, &byte, 1);
    printf("Read byte %c\n", byte);

    if(close(fd) < 0)
    {
	    return 1;
    }
    return 0;
}
