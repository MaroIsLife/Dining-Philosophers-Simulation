#include "philo.h"

void	init(int ac, char **av, t_source *src)
{
	int	i;

	if (ac > 6 || ac < 5)
	{
		printf("Error\n");
		exit(1);
	}
	pthread_mutex_init(&src->lock, NULL);
	src->p_num = ft_my_atoi(av[1]);
	src->time_to_die = ft_my_atoi(av[2]);
	src->time_to_eat = ft_my_atoi(av[3]);
	src->time_to_sleep = ft_my_atoi(av[4]);
	if (ac == 6)
		src->n_must_eat = ft_my_atoi(av[5]);
	else
		src->n_must_eat = 0;
	src->n_forks = malloc(src->p_num * sizeof(pthread_mutex_t));
	i = 0;
	while (i < src->p_num)
	{
		pthread_mutex_init(&src->n_forks[i], NULL);
		i++;
	}
}

ssize_t	get_time(void)
{
	struct timeval	time;
	ssize_t			test;

	gettimeofday(&time, NULL);
	test = time.tv_usec + (time.tv_sec * 1000000);
	return (test);
}

void	ft_sleep(ssize_t time)
{
	ssize_t	r;
	ssize_t	mic;

	mic = get_time();
	r = time - 60;
	usleep(r * 1000);
	while ((get_time() - mic) < (time * 1000))
	{
	}
}

void	print_philo(int id, char *s, int option)
{
	t_source		*src;
	struct timeval	time;
	ssize_t			test;
	char			*s1;

	if (option == 1)
		s1 = "\033[0;32m%lld %d %s\033[0m\n";
	else if (option == 2)
		s1 = "\033[0;33m%lld %d %s\033[0m\n";
	else if (option == 3)
		s1 = "\033[0;35m%lld %d %s\033[0m\n";
	src = source_static();
	pthread_mutex_lock(&src->lock);
	gettimeofday(&time, NULL);
	test = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	printf(s1, test, id, s);
	pthread_mutex_unlock(&src->lock);
}

void	print_death(int id)
{
	t_source	*src;

	src = source_static();
	pthread_mutex_lock(&src->lock);
	printf("\033[0;31m%zd %d died\033[0m\n", get_time(), id + 1);
}
