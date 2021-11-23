#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int ac, char *av[])
{
	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];

	if ((ac != 3) && (ac != 4))
	{
		fprintf(stderr, "usage: %s source destination and source -i\n", *av);
		exit(1);
	}

	if (ac == 4)
	{
		if (strcmp("-i", av[1]))
			oops("Incorrect argumen", *av);
	}

	int fp;
	if ((fp = open(av[3], O_RDONLY)) == -1)
	{
	        printf("cp: overwrite %s ?", av[3]);
		close(fp);
		char ch;
		ch = getchar();
		if (ch != 'y')
		    return 0;
        }

	

	if (strcmp(av[1], av[2]) == 0)
	{
		fprintf(stderr, "are you copy %s not copy %s\n", av[1], av[2]);
		exit(1);
	}

	if ((in_fd = open(av[1], O_RDONLY)) == -1)
		oops("Cannot creat", av[2]);

	if ((out_fd = creat(av[2], COPYMODE)) == -1)
		oops("Cannot creat", av[2]);

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
	{
		if (write(out_fd, buf, n_chars) != n_chars)
			oops("Write error to ", av[2]);
	}

	if (n_chars == -1)
		oops("Read error from ", av[1]);

	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}


