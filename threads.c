#include "philo.h"

int	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	taking_forks_and_eating(t_params *argument, int i)
{
	pthread_mutex_lock(&argument->forks[argument->philosofer[i]->left_fork]);
	pthread_mutex_lock(&argument->print);
	printf("%d %d has taken a fork\n", gettime() - argument->time_zero, i + 1);
	pthread_mutex_unlock(&argument->print);
	if (argument->number_of_philosophers == 1)
	{
		usleep(argument->time_to_die * 1000);
		argument->flag_die = i;
	}
	pthread_mutex_lock(&argument->forks[argument->philosofer[i]->right_fork]);
	pthread_mutex_lock(&argument->print);
	printf("%d %d has taken a fork\n", gettime() - argument->time_zero, i + 1);
	pthread_mutex_unlock(&argument->print);
	pthread_mutex_lock(&argument->death[i]);
	argument->philosofer[i]->life_time = gettime();
	pthread_mutex_unlock(&argument->death[i]);
	pthread_mutex_lock(&argument->print);
	printf("%d %d is eating\n", gettime() - argument->time_zero, i + 1);
	pthread_mutex_unlock(&argument->print);
	usleep(argument->time_to_eat);
	pthread_mutex_unlock(&argument->forks[argument->philosofer[i]->left_fork]);
	pthread_mutex_unlock(&argument->forks[argument->philosofer[i]->right_fork]);
	argument->philosofer[i]->meal_count++;
	return ;
}

void	*start_philo(void *ptr)
{
	t_params		*argument;
	int				i;

	argument = (t_params *)ptr;
	i = argument->i_philosofer;
	argument->philosofer[i]->life_time = gettime();
	argument->philosofer[i]->meal_count = 0;
	while (1)
	{
		taking_forks_and_eating(argument, i);
		pthread_mutex_lock(&argument->print);
		printf("%d %d is sleeping\n", gettime() - argument->time_zero, i + 1);
		pthread_mutex_unlock(&argument->print);
		usleep(argument->time_to_sleep);
		pthread_mutex_lock(&argument->print);
		printf("%d %d is thinking\n", gettime() - argument->time_zero, i + 1);
		pthread_mutex_unlock(&argument->print);
	}
	return (NULL);
}

void	*start_checker(void *ptr)
{
	t_params		*argument;
	int				i;
	int				delta_us;

	argument = (t_params *)ptr;
	i = 0;
	while (1)
	{
		while (i < argument->number_of_philosophers)
		{
			pthread_mutex_lock(&argument->death[i]);
			delta_us = gettime() - argument->philosofer[i]->life_time;
			if (delta_us >= argument->time_to_die)
				argument->flag_die = i;
			if (argument->flag_die == -1)
				pthread_mutex_unlock(&argument->death[i]);
			i++;
		}
		i = 0;
	}
	return (NULL);
}

int	make_threads(t_params *argument, int i)
{
	argument->philo_threads = (pthread_t *)malloc(sizeof(pthread_t)
			* argument->number_of_philosophers);
	if (!argument->philo_threads)
		return (ft_errors(3));
	argument->time_zero = gettime();
	while (++i < argument->number_of_philosophers)
	{
		argument->i_philosofer = i;
		if (pthread_create(&argument->philo_threads[i], NULL, start_philo,
				argument))
			return (ft_errors(5));
		usleep(500);
		pthread_detach(argument->philo_threads[i]);
	}
	if (pthread_create(&argument->checker, NULL, start_checker, argument))
		return (ft_errors(5));
	pthread_detach(argument->checker);
	return (0);
}
