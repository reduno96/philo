#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_initialize_value(t_philosopher *philo)
{
	philo->id = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->think = 0;
	philo->eat = 0;
}
void	*thread_function(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{

		thinking(philo);
		// eating(philo);
		// sleeping(philo);
	}
	return (NULL);
}

void	ft_initialize_data(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = i;
		philo[i].left_fork = i - 1;
		if (i == 0)
			philo[i].left_fork = philo->data.num_of_philo;
		i++;
	}
}

void	create_philos(t_philosopher *philo)
{
	int	i;

	i = 0;
	i = 0;
	while (i < philo->data.num_of_philo)
	{
		if (pthread_create(&philo[i].theard, NULL, thread_function,
				&philo[i]) != 0)
		{
			ft_put_error("Failed to Create The Theard");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->data.num_of_philo)
	{
		if (pthread_join(philo[i].theard, NULL) != 0)
		{
			ft_put_error("Failed To Join Thread");
			return ;
		}
		i++;
	}
}

int	ft_check_arg(t_check argument)
{
	if (argument.num_of_philo <= 0 || argument.time_to_die <= 0)
	{
		ft_put_error("We do not allow the use of zero or negative numbers as arguments.");
		return (0);
	}
	return (1);
}
void	ft_start_threads(char **av)
{
	t_philosopher	*philosophers;
	t_check			argument;

	philosophers = NULL;
	argument.num_of_philo = ft_atoi(av[1]);
	argument.time_to_eat = ft_atoi(av[2]);
	argument.time_to_sleep = ft_atoi(av[3]);
	argument.time_to_die = ft_atoi(av[4]);
	if (av[5])
		argument.philo_eat_limit = ft_atoi(av[5]);
	else
		argument.philo_eat_limit = 0;
	if (!ft_check_arg(argument))
		return ;
	philosophers = malloc(argument.num_of_philo * sizeof(t_philosopher));
	if (!philosophers)
		return ;
	philosophers->data = argument;
	ft_initialize_data(philosophers);
	create_philos(philosophers);
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
