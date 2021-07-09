SRC = main.c ft_my_atoi.c utils.c

all: philo

philo:
	@#@$(CC) $(SRC) $(GN) $(LIB) -g -o philo -Wall -Wextra -Werror -Werror
	@$(CC) $(SRC) $(GN) $(LIB) -g -o philo
clean :
	@rm -rf philo.o
fclean : clean
		@rm -rf ./philo philo.dSYM
re : fclean all

.PHONY : all clean fclean re $(NAME)