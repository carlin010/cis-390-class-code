#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int n;
	int pipefd[2];
	
    // Create Pipe
	int ret = pipe(pipefd); 
    if (ret == -1) {
        perror("pipe() failed");
        return 1;
    }

    // Write to pipe
    char buf[1025];
	char *data = "hello... this is sample data";
	int bytes_written = write(pipefd[1], data, strlen(data));
    printf("Wrote %d bytes to the pipe\n", bytes_written);
    close(pipefd[1]);

    // Read from pipe
	if ((n = read(pipefd[0], buf, 1024)) >= 0) { 
		buf[n] = 0;
		printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
        close(pipefd[0]);
	}	
	else
		perror("read");
	exit(0);
}
