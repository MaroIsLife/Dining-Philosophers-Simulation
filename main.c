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
	pthread_mutex_init(&src->lock,NULL);
	src->p_num = ft_my_atoi(av[1]);
	
	
	src->time_to_die = ft_my_atoi(av[2]);
	src->time_to_eat = ft_my_atoi(av[3]);
	src->time_to_sleep = ft_my_atoi(av[4]);
	if (ac == 6)
		src->n_must_eat = ft_my_atoi(av[5]);
	else
		src->n_must_eat = 0;
	src->n_forks = malloc(src->p_num * sizeof(pthread_mutex_t));
	int i  = 0;
	while(i < src->p_num)
	{
		pthread_mutex_init(&src->n_forks[i], NULL);
		i++;
	}
}

void	print_philo(char *str, int n)
{
	t_source *src;

	src = source_static();
	pthread_mutex_lock(&src->lock);
	printf("%d %s\n", n , str);
	pthread_mutex_unlock(&src->lock);
}

void	*main_fun(void *arg)
{
	//int i = 0;
	t_id *ss;
	t_source *src;

	src = source_static();
	ss = (t_id *)arg;

	pthread_mutex_lock(&src->n_forks[ss->p_id - 1]);
	printf("%d Has taken a fork 1\n",ss->p_id);
	pthread_mutex_lock(&src->n_forks[ss->p_id % src->p_num]);
	printf("%d Has taken a fork 2\n",ss->p_id);
	printf("%d Philo Is eating\n",ss->p_id);
	usleep(src->time_to_eat * 1000);
	pthread_mutex_unlock(&src->n_forks[ss->p_id % src->p_num]);
	pthread_mutex_unlock(&src->n_forks[ss->p_id - 1]);
	printf("%d Philo Is sleeping\n",ss->p_id);
	usleep(src->time_to_sleep * 1000);
	printf("%d Philo Is thinking\n",ss->p_id);


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
		pthread_create(&newthread[i], NULL, main_fun, &ss[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	return (0);
}