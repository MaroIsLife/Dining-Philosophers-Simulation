#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>


typedef struct	s_id
{
	int	p_id;

}	t_id;


typedef struct	s_source
{
	int	p_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_must_eat;
	int	n_forks;
	t_id *ss;
}	t_source;

long long	ft_my_atoi(const char *str);

#endif