#include "philo.h"
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t	mutex;
int				mails = 0;

void	ft_initialize_value(t_philosopher *philo)
{
	philo->think = 0;
	philo->eating = 0;
	philo->last_meal = 0;
	philo->data->end = 1;
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0 || philo->id == philo->data->num_of_philo)
		sleeping(philo);
	while (philo->data->end == 1
			/* && philo->eating < philo->data->philo_eat_limit */)
	{
		eating(philo);
		// thinking(philo);
		// sleeping(philo);
	}
	return (NULL);
}

// void	ft_initialize_data(t_philosopher *philo, t_share *argument)
// {
// 	int		i;
// 	t_fork	*forks;

// 	forks = malloc(argument->num_of_philo * sizeof(t_fork));
// 	i = 0;
// 	while (i < argument->num_of_philo)
// 	{
// 		philo[i].data = argument;
// 		philo[i].creation_time = ft_get_time();
// 		philo[i].id = i + 1;
// 		philo[i].j = i;
// 		forks[i].right_fork = i;
// 		forks[i].left_fork = (i + 1) % philo[i].data->num_of_philo;
// 		philo[i].data->forks = forks;
// 		pthread_mutex_init(&philo[i].data->forks[i].mutex_right_f, NULL);
// 		pthread_mutex_init(&philo[i].data->forks[(i + 1)
// 			% philo[i].data->num_of_philo].mutex_left_f, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < argument->num_of_philo)
// 	{
// 		i++;
// 	}
// }

void	ft_initialize_data(t_philosopher *philo, t_share *argument)
{
	int	i;

	argument->forks = malloc(argument->num_of_philo * sizeof(t_fork));
	i = 0;
	while (i < argument->num_of_philo)
	{
		philo[i].creation_time = ft_get_time();
		philo[i].id = i + 1;
		philo[i].j = i;
		argument->forks[i].right_fork = i;
		pthread_mutex_init(&argument->forks[i].mutex, NULL);
		philo[i].data = argument;
		i++;
	}
	i = 0;
	while (i < argument->num_of_philo)
	{
		i++;
	}
}
void	create_philos(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		if (pthread_create(&philo[i].theard, NULL, &routine, &philo[i]) != 0)
		{
			ft_put_error("Failed to Create The Theard");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->data->num_of_philo)
	{
		if (pthread_join(philo[i].theard, NULL) != 0)
		{
			ft_put_error("Failed To Join Thread");
			return ;
		}
		i++;
	}
}

int	ft_check_arg(t_share *argument)
{
	if (argument->num_of_philo <= 0 || argument->time_to_die <= 0)
	{
		ft_put_error("We do not allow the use of zero or negative numbers as arguments.");
		return (0);
	}
	return (1);
}
void	ft_start_threads(char **av)
{
	t_philosopher	*philosophers;
	t_share			argument;

	philosophers = NULL;
	argument.num_of_philo = ft_atoi(av[1]);
	argument.time_to_eat = ft_atoi(av[2]);
	argument.time_to_sleep = ft_atoi(av[3]);
	argument.time_to_die = ft_atoi(av[4]);
	if (av[5])
		argument.philo_eat_limit = ft_atoi(av[5]);
	else
		argument.philo_eat_limit = 0;
	if (!ft_check_arg(&argument))
		return ;
	philosophers = malloc(argument.num_of_philo * sizeof(t_philosopher));
	if (!philosophers)
		return ;
	ft_initialize_data(philosophers, &argument);
	ft_initialize_value(philosophers);
	create_philos(philosophers);
	free(philosophers);
	pthread_mutex_destroy(&mutex);
}
int	main(int ac, char **av)
{
	(void)ac;
	if (ac == 5 || ac == 6)
		ft_start_threads(av);
	else
		ft_put_error("The argument not allowed\n");
	return (0);
}
