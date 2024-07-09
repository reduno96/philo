/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:00:03 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/09 00:11:53 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_initialize_value(t_philosopher *philo)
{
	philo->eating = 0;
	philo->last_meal = 0;
	philo->data->end = 1;
}

void	ft_print_actions(t_philosopher *philo, char action)
{
	if (action == 'D' && philo->data->end != 0)
	{
		philo->data->end = 1;
		printf("%lld %d died\n", get_time_passed(philo->creation_time),
			philo->id);
	}
	else if (philo->data->end != 0)
	{
		if (action == 'T')
			printf("%lld %d is thinking\n",
				get_time_passed(philo->creation_time), philo->id);
		else if (action == 'G')
			printf("%lld %d has taken a fork\n",
				get_time_passed(philo->creation_time), philo->id);
		else if (action == 'E')
			printf("%lld %d is eating\n", get_time_passed(philo->creation_time),
				philo->id);
		else if (action == 'S')
			printf("%lld %d is sleeping\n",
				get_time_passed(philo->creation_time), philo->id);
	}
}

int	ft_limit(t_share *philo)
{
	if (philo->limit != -1)
	{
		if (philo->philo_eat_limit <= 0)
			return (1);
		else
			return (0);
	}
	return (0);
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
		if (eating(philo))
			break ;
		if (thinking(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (get_time_passed(philo->last_meal) > philo->data->time_to_die
			|| (get_time_passed(philo->last_meal) > philo->data->time_to_eat
				+ philo->data->time_to_sleep))
		{
			philo->data->end = 0;
			ft_print_actions(philo, 'D');
			break ;
		}
	}
	return (NULL);
}

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
	pthread_mutex_init(&argument->print, NULL);
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
		usleep(100);
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
	if (argument->num_of_philo <= 0 || argument->num_of_philo > 200
		|| argument->time_to_die <= 60 || argument->time_to_eat <= 60
		|| argument->time_to_sleep <= 60 || ft_limit(argument))
	{
		ft_put_error("Error: This input is not allowed.\n");
		return (0);
	}
	return (1);
}

void	*routine_one_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		printf("%lld %d has taken a fork\n",
			get_time_passed(philo->creation_time), philo->id);
		printf("%lld %d is eating\n", get_time_passed(philo->creation_time),
			philo->id);
		philo->last_meal = ft_get_time();
		if (ft_usleep_to_eat(philo)
			|| get_time_passed(philo->last_meal) > philo->data->time_to_die
			|| (philo->data->time_to_sleep
				+ philo->data->time_to_eat) > philo->data->time_to_die)
		{
			printf("%lld %d died\n", get_time_passed(philo->creation_time),
				philo->id);
			break ;
		}
		printf("%lld %d is thinking\n", get_time_passed(philo->creation_time),
			philo->id);
		printf("%lld %d is sleeping\n", get_time_passed(philo->creation_time),
			philo->id);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}
void	create_one_philo(t_philosopher *philo)
{
	if (pthread_create(&philo->theard, NULL, routine_one_philo, philo) != 0)
	{
		ft_put_error("Failed to Create The Theard");
		return ;
	}
	if (pthread_join(philo->theard, NULL) != 0)
	{
		ft_put_error("Failed To Join Thread");
		return ;
	}
}

void	ft_start_threads(char **av)
{
	t_philosopher	*philosophers;
	t_share			argument;
	int				i;

	philosophers = NULL;
	argument.num_of_philo = ft_atoi(av[1]);
	argument.time_to_die = ft_atoi(av[2]);
	argument.time_to_eat = ft_atoi(av[3]);
	argument.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		argument.philo_eat_limit = ft_atoi(av[5]);
	else
	{
		argument.philo_eat_limit = 0;
		argument.limit = -1;
	}
	if (!ft_check_arg(&argument))
		return ;
	philosophers = malloc(argument.num_of_philo * sizeof(t_philosopher));
	if (!philosophers)
		return ;
	ft_initialize_data(philosophers, &argument);
	ft_initialize_value(philosophers);
	if (philosophers->data->num_of_philo == 1)
		create_one_philo(philosophers);
	else
		create_philos(philosophers);
	free(philosophers);
	pthread_mutex_destroy(&argument.print);
	i = 0;
	while (argument.num_of_philo > i)
	{
		pthread_mutex_destroy(&argument.forks[i].mutex);
		i++;
	}
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
