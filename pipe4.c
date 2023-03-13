#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[])
{
    int data_processed;
    char buffer[BUFSIZ + 1];
    int file_descriptor;
    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    data_processed = read(file_descriptor, buffer, BUFSIZ);
    printf("Read %d bytes: %s\n - %d", data_processed, buffer, getpid());
    exit(EXIT_SUCCESS);
}