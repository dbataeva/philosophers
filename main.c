#include "philo.h"

int	ft_errors(int err)
{
	if (err == 1)
		write(2, "wrong number of arguments\n", 26);
	else if (err == 2)
		write(2, "wrong format of arguments\n", 26);
	else if (err == 3)
		write(2, "not enough space\n", 17);
	else if (err == 4)
		write(2, "error while mutex init\n", 23);
	else if (err == 5)
		write(2, "error while thread init\n", 24);
	return (1);
}

void	ft_free(t_params *argument, int i)
{
	if (argument->philo_threads)
		free(argument->philo_threads);
	if (argument->forks)
	{
		while (i < argument->number_of_philosophers)
		{
			pthread_mutex_destroy(&argument->forks[i]);
			pthread_mutex_destroy(&argument->death[i]);
			i++;
		}
		free(argument->forks);
	}
	pthread_mutex_destroy(&argument->print);
	i = 0;
	if (argument->philosofer)
	{
		while (i < argument->number_of_philosophers && argument->philosofer[i])
		{
			free(argument->philosofer[i]);
			i++;
		}
		free(argument->philosofer);
	}
}

void	the_end(t_params *argument, int end_flag, int i)
{
	while (1)
	{
		if (argument->flag_die != -1)
		{
			pthread_mutex_lock(&argument->print);
			printf("%d %d died\n", gettime() - argument->time_zero,
				argument->flag_die + 1);
			break ;
		}
		end_flag = 1;
		while (argument->flag_n_eat && (++i < argument->number_of_philosophers))
		{
			if (argument->philosofer[i]->meal_count
				< argument->number_of_times_each_philosopher_must_eat)
				end_flag = 0;
		}
		if (end_flag && argument->flag_n_eat)
		{
			pthread_mutex_lock(&argument->print);
			break ;
		}
		i = 0;
	}
	ft_free(argument, 0);
}

int	main(int argc, char **argv)
{
	t_params		argument;
	int				i;
	int				end_flag;		

	if (parsing(&argument, argc, argv))
		return (1);
	argument.forks = NULL;
	if (make_mutex(&argument))
		return (1);
	argument.philosofer = NULL;
	if (make_philos(&argument))
		return (1);
	argument.philo_threads = NULL;
	if (make_threads(&argument, -1))
		return (1);
	the_end(&argument, 1, -1);
	return (0);
}
