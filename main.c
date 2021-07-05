#include "philosophers.h"

void	init(int ac, char **av, t_source *src)
{
	src->p_num = ft_my_atoi(av[1]);
	src->time_to_die = ft_my_atoi(av[2]);
	src->time_to_eat = ft_my_atoi(av[3]);
	src->time_to_sleep = ft_my_atoi(av[4]);
	if (ac == 6)
		src->n_must_eat = ft_my_atoi(av[5]);
	else
		src->n_must_eat = 0;
}

int	main(int ac, char **av)
{
	t_source	src;
	
	init(ac, av, &src);

	return (0);
}