#include "philo.h"

t_source	*source_static(void)
{
	static t_source	src;

	return (&src);
}

void	init(int ac, char **av, t_source *src)
{
	if (ac > 6 || ac < 5)
	{
		printf("Error\n");
		exit(1);
	}
	src->p_num = ft_my_atoi(av[1]);
	src->n_forks = src->p_num;
	src->time_to_die = ft_my_atoi(av[2]);
	src->time_to_eat = ft_my_atoi(av[3]);
	src->time_to_sleep = ft_my_atoi(av[4]);
	if (ac == 6)
		src->n_must_eat = ft_my_atoi(av[5]);
	else
		src->n_must_eat = 0;
}

void	*myturn(void *arg)
{
	int i = 0;
	t_id *ss;

	ss = (t_id *)arg;
	printf("Philo is eating %d\n",ss->p_id);
	i++;
	sleep(1);
	return NULL;
}


int	main(int ac, char **av)
{
	pthread_t 	*newthread;
	int i;
	t_id *ss;
	t_source *src;

	src = source_static();
	init(ac, av, src);
	ss = malloc(src->p_num * sizeof(t_source));
	newthread = malloc(src->p_num *sizeof(pthread_t));
	i = 0;
	while(i < src->p_num)
	{
		ss[i].p_id = i + 1;
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		pthread_create(&newthread[i], NULL, myturn, &ss[i]);
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	// myturn();
	// yourturn();
	return (0);
}