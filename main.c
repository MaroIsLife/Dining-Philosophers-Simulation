#include "philo.h"

t_source	*source_static(void)
{
	static t_source	src;

	return (&src);
}

int	last_ate(void)
{
	int			i;
	t_source	*src;

	src = source_static();
	while (1)
	{
		i = 0;
		while (i < src->p_num)
		{
			if ((get_time() - src->philo_last_ate[i])
				>= (src->time_to_die * 1000))
			{
				print_death(i);
				return (1);
			}
			i++;
		}
		if (src->test >= (src->n_must_eat * src->p_num) && src->n_must_eat > 0)
			return (1);
		usleep(10);
	}
	return (0);
}

void	*main_fun(void *arg)
{
	t_id		*ss;
	t_source	*src;

	while (1)
	{
		src = source_static();
		ss = (t_id *)arg;
		pthread_mutex_lock(&src->n_forks[ss->p_id - 1]);
		print_philo(ss->p_id, "has taken a fork", 1);
		pthread_mutex_lock(&src->n_forks[ss->p_id % src->p_num]);
		print_philo(ss->p_id, "has taken a fork", 1);
		src->philo_last_ate[ss->p_id - 1] = get_time();
		pthread_mutex_lock(&src->lock);
		src->test++;
		pthread_mutex_unlock(&src->lock);
		print_philo(ss->p_id, "is eating", 2);
		ft_sleep(src->time_to_eat);
		pthread_mutex_unlock(&src->n_forks[ss->p_id % src->p_num]);
		pthread_mutex_unlock(&src->n_forks[ss->p_id - 1]);
		print_philo(ss->p_id, "is sleeping", 3);
		ft_sleep(src->time_to_sleep);
		print_philo(ss->p_id, "is thinking", 3);
	}
	return (NULL);
}

int	main_two(t_id *ss, t_source *src, int i, pthread_t	*newthread)
{
	while (i < src->p_num)
	{
		ss[i].p_id = i + 1;
		i++;
	}
	i = 0;
	while (i < src->p_num)
	{
		src->philo_last_ate[i] = get_time();
		pthread_create(&newthread[i], NULL, main_fun, &ss[i]);
		usleep(100);
		i++;
	}
	i = 0;
	if (last_ate() == 1)
		return (1);
	while (i < src->p_num)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	i = 0;
	while (i < src->p_num)
		pthread_mutex_destroy(&src->n_forks[i++]);
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*newthread;
	int			i;
	t_id		*ss;
	t_source	*src;

	src = source_static();
	init(ac, av, src);
	ss = malloc(src->p_num * sizeof(t_source));
	newthread = malloc(src->p_num * sizeof(pthread_t));
	src->philo_last_ate = malloc(src->p_num * sizeof(ssize_t));
	src->test = 0;
	i = 0;
	main_two(ss, src, 0, newthread);
	free(ss);
	free(src->philo_last_ate);
	free(newthread);
	free(src->n_forks);
	return (0);
}
