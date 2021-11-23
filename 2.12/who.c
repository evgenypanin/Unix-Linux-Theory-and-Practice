#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "utmplib.h"

void show_info(struct utmp *);
void show_time(long);

int main()
{
	struct utmp *utbufp;
	if (utmp_open(UTMP_FILE) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}

	while ((utbufp = utmp_next()) != (struct utmp*)NULL)
		show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if (utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s", utbufp->ut_user);
	printf("%-8.8s", utbufp->ut_line);
	show_time(utbufp->ut_time);
	printf("(%s)", utbufp->ut_host);
	printf("\n");
}

void show_time(long timeval)
{
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s", cp+4);
}
