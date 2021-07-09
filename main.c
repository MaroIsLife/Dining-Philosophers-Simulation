#include "philo.h"

t_source	*source_static(void)
{
	static t_source	src;

	return (&src);
}


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
	while(i < src->p_num)
	{
		pthread_mutex_init(&src->n_forks[i], NULL);
		i++;
	}
}

ssize_t get_time()
{
	struct timeval val;

	gettimeofday(&val, NULL);
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}


void	ft_sleep(ssize_t time)
{
	ssize_t time_end; //Milliseconds

	time_end = get_time() + time;
	while (get_time() < time_end)
	{
		usleep(100);
	}
}

void	print_philo(int id, char *s)
{
	t_source *src;
	long long		time;
	struct timeval	val;

	src = source_static();
	pthread_mutex_lock(&src->lock);
	time = get_time();
	printf("%lld %d %s\n", time, id, s);
	pthread_mutex_unlock(&src->lock);
}


void	print_death(int id)
{
	t_source *src;

	src = source_static();
	
	pthread_mutex_lock(&src->lock);
	printf("%d died\n", id + 1);
	return ;
	pthread_mutex_unlock(&src->lock);




}

int	last_ate()
{
	int	i;
	t_source *src;
	
	src = source_static();
	while (1)
	{
		i = 0;
		while (i < src->p_num)
		{
			if ((get_time() - src->philo_last_ate[i]) >= src->time_to_die)
			{
				print_death(i);
				return (1);
			}
			i++;
		}
		usleep(15); //Just to not force on the process
	}
	return (0);
}

void	*main_fun(void *arg)
{
	t_id *ss;
	t_source *src;


	while (1)
	{
		src = source_static();
		ss = (t_id *)arg;
		pthread_mutex_lock(&src->n_forks[ss->p_id - 1]);
		print_philo(ss->p_id,"as taken a fork");
		pthread_mutex_lock(&src->n_forks[ss->p_id % src->p_num]);
		print_philo(ss->p_id,"as taken a fork");
		src->philo_last_ate[ss->p_id - 1] = get_time();
		print_philo(ss->p_id, "is eating");
		ft_sleep(src->time_to_eat);
		pthread_mutex_unlock(&src->n_forks[ss->p_id % src->p_num]);
		pthread_mutex_unlock(&src->n_forks[ss->p_id - 1]);
		print_philo(ss->p_id, "is sleeping");
		ft_sleep(src->time_to_sleep);
		print_philo(ss->p_id, "is thinking");
	}


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
	src->philo_last_ate = malloc(src->p_num * sizeof(long long));
	i = 0;
	while(i < src->p_num)
	{
		ss[i].p_id = i + 1;
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		src->philo_last_ate[i] = get_time();
		pthread_create(&newthread[i], NULL, main_fun, &ss[i]);
		ft_sleep(100);
		i++;
	}
	i = 0;
	if (last_ate() == 1)
	{
		return (1);
	}
	while (i < src->p_num)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		pthread_mutex_destroy(&src->n_forks[i]);
		i++;
	}
	return (0);
}