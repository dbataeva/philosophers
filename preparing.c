#include "philo.h"

t_philo	*make_philo(t_params *argument, int i)
{
	t_philo		*philosofer;

	philosofer = (struct s_philo *)malloc(sizeof(t_philo));
	if (!philosofer)
		return (NULL);
	else
	{
		philosofer->right_fork = (i + 1) % argument->number_of_philosophers;
		philosofer->left_fork = i;
	}
	return (philosofer);
}

int	make_philos(t_params *argument)
{
	int	i;

	i = 0;
	argument->philosofer = (struct s_philo **)malloc(sizeof(t_philo *)
			* argument->number_of_philosophers);
	if (!argument->philosofer)
		return (ft_errors(3));
	while (i < argument->number_of_philosophers)
	{
		argument->philosofer[i] = make_philo(argument, i);
		if (!argument->philosofer[i])
			return (ft_errors(3));
		i++;
	}
	return (0);
}

int	make_mutex(t_params *argument)
{
	int	i;

	i = 0;
	argument->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* argument->number_of_philosophers);
	if (!argument->forks)
		return (ft_errors(3));
	argument->death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* argument->number_of_philosophers);
	if (!argument->death)
		return (ft_errors(3));
	while (i < argument->number_of_philosophers)
	{
		if (pthread_mutex_init(&argument->forks[i], NULL))
			return (ft_errors(4));
		if (pthread_mutex_init(&argument->death[i], NULL))
			return (ft_errors(4));
		i++;
	}
	if (pthread_mutex_init(&argument->print, NULL))
		return (ft_errors(4));
	return (0);
}

int	check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(t_params *argument, int argc, char **argv)
{
	pthread_t	checker;

	argument->flag_n_eat = 1;
	argument->checker = checker;
	argument->flag_die = -1;
	if ((argc != 5) && (argc != 6))
		return (ft_errors(1));
	if (check_arguments(argv))
		return (ft_errors(2));
	argument->number_of_philosophers = ft_atoi(argv[1]);
	argument->time_to_die = ft_atoi(argv[2]);
	argument->time_to_eat = ft_atoi(argv[3]) * 1000;
	argument->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		argument->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		argument->flag_n_eat = 0;
	return (0);
}
