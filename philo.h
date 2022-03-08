#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	left_fork;
	int	right_fork;
	int	life_time;
	int	meal_count;
}				t_philo;

typedef struct s_params
{
	unsigned int	number_of_philosophers;
	int				time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	int				flag_n_eat;
	int				flag_die;
	int				time_zero;
	int				i_philosofer;
	t_philo			**philosofer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death;
	pthread_mutex_t	print;
	pthread_t		checker;
	pthread_t		*philo_threads;

}				t_params;

int	make_philos(t_params *argument);
int	make_mutex(t_params *argument);
int	parsing(t_params *argument, int argc, char **argv);
int	check_arguments(char **argv);
int	make_threads(t_params *argument, int i);
int	gettime(void);
int	ft_atoi(const char *str);
int	ft_isdigit(int ch);
int	ft_errors(int err);

#endif