#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>

#define SHOWHOST

void show_info(struct utmp*);

int main()
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}

	while ((read(utmpfd, &current_record, reclen)) == reclen)
			show_info(&current_record);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	printf("%10d", utbufp->ut_time);
	printf(" ");
#ifndef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf(" ");
	printf("%s", utbufp->ut_id);
	printf(" ");
	printf("%d", utbufp->ut_type);
        printf(" ");
        printf("%d", utbufp->ut_exit.e_termination);
        printf(" ");
        printf("%d", utbufp->ut_exit.e_exit);	
	printf("\n");
}


