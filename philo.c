#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_initialize_value(t_philosopher *philo)
{
	philo->id = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->number_of_philosophers = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->time_to_die = 0;
	philo->semaphore = 1;
	philo->think = 0;
	philo->eat = 0;

}
void	*thread_function(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		thinking(philosopher);
		// eating(philosopher);
		// sleeping(philosopher);
	}
	return (NULL);
}

void	ft_initialize_data(t_philosopher *philosophers, t_check argument)
{
	int	i;

	i = 0;
	while (i < argument.number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].right_fork = i;
		philosophers[i].left_fork = i - 1;
		if (i == 0)
			philosophers[i].left_fork = argument.number_of_philosophers - 1;
		philosophers[i].number_of_philosophers = argument.number_of_philosophers;
		philosophers[i].time_to_die = argument.time_to_die;
		philosophers[i].time_to_eat = argument.time_to_eat;
		philosophers[i].time_to_sleep = argument.time_to_sleep;
		i++;
	}
}

void	create_philos(t_philosopher *philosophers, t_check argument)
{
	int	i;

	i = 0;
	ft_initialize_data(philosophers, argument);
	i = 0;
	while (i < argument.number_of_philosophers)
	{
		if (pthread_create(&philosophers[i].theard, NULL, thread_function,
				&philosophers[i]) != 0)
		{
			ft_put_error("Failed to Create The Theard");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < argument.number_of_philosophers)
	{
		if (pthread_join(philosophers[i].theard, NULL) != 0)
		{
			ft_put_error("Failed To Join Thread");
			return ;
		}
		i++;
	}
}

int	ft_check_arg(t_check argument)
{
	if (argument.number_of_philosophers <= 0 || argument.time_to_die <= 0
		|| argument.time_to_eat <= argument.time_to_sleep)
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
	argument.number_of_philosophers = atoi(av[1]);
	argument.time_to_eat = atoi(av[2]);
	argument.time_to_sleep = atoi(av[3]);
	argument.time_to_die = atoi(av[4]);
	if (!ft_check_arg(argument))
		return ;
	philosophers = malloc(argument.number_of_philosophers
			* sizeof(t_philosopher));
	if (!philosophers)
		return ;
	philosophers->number_of_philosophers = argument.number_of_philosophers;
	philosophers->time_to_die = argument.time_to_die;
	philosophers->time_to_eat = argument.time_to_eat;
	philosophers->time_to_sleep = argument.time_to_sleep;
	create_philos(philosophers, argument);
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
