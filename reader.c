#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>    
#include <string.h>

#define MAX_LEN 20

int main(int argc, char ** argv) {
    char newFile[80];
    bool willWrite = false;
    if(argc != 2)
    {
	    printf("usage: <reader> <fileName>");
	    return -1;
    }

    if(argc == 2)
    {
	    strcpy(newFile, argv[1]);
	    willWrite = true;
    }
    char byte;
    char output[80];
    int fd = open("/dev/533final", O_RDWR | O_APPEND);

    int n = 80;
    int i;

    for(i = 0; i < n - 1; i++)
    {
	    ssize_t size = read(fd, &output[i], 100);
    }

    printf("File had: %s\n", output);

    if(close(fd) < 0)
    {
	    return 1;
    }
    FILE * fp = fopen(newFile, "a");
    fputs(output, fp);
    fclose(fp);


    return 0;
}
