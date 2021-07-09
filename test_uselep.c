
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>


//long long	get_in_mic(void)
//{
//	struct timeval	time;
//	long long		h;

//	gettimeofday(&time, NULL);
//	h = time.tv_usec + (time.tv_sec * 1000000);
//	return (h);
//}
unsigned long long	get_in_mic(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void	my_sleep(long long time)
{
	unsigned long long	start;
	unsigned long long	end;

	start = get_in_mic();
	end = start + time;
	// usleep((time - 40) * 1000);
	while (get_in_mic() < end)
		;
}

int main()
{
	printf("time now: %lld\n",get_in_mic());
	my_sleep(100);
	printf("time then: %lld\n",get_in_mic());
	return (0);
}