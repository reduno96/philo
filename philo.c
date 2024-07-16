/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:00:03 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/16 14:45:38 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_initialize_value(t_philosopher *philo)
{
	philo->eating = 0;
	philo->data->end = 1;
}

void	ft_print_actions(t_philosopher *philo, char action)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	if (ft_get_end_value(philo) == 1)
	{
		if (action == 'T')
			printf("%lld %d is thinking\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'R')
			printf("%lld %d has taken a fork\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'L')
			printf("%lld %d has taken a fork\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'E')
			printf("%lld %d is eating\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'S')
			printf("%lld %d is sleeping\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->mtx_print);
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

void	ft_initialize_data(t_philosopher *philo, t_share *argument)
{
	int	i;

	argument->forks = malloc(argument->num_of_philo * sizeof(t_fork));
	argument->creation_time = ft_get_time();
	i = 0;
	while (i < argument->num_of_philo)
	{
		philo[i].last_meal = ft_get_time();
		philo[i].id = i + 1;
		philo[i].j = i;
		argument->forks[i].right_fork = i;
		pthread_mutex_init(&argument->forks[i].mutex, NULL);
		philo[i].data = argument;
		i++;
	}
	pthread_mutex_init(&argument->mtx_print, NULL);
	pthread_mutex_init(&argument->mtx_end, NULL);
	pthread_mutex_init(&argument->mtx_time, NULL);
}
void	ft_print_died(t_philosopher philo)
{
	pthread_mutex_lock(&philo.data->mtx_print);
	printf("\033[31m%lld %d died\033[0m\n", get_time_passed(&philo,
			philo.data->creation_time), philo.id);
	ft_change_end_value(&philo);
	pthread_mutex_unlock(&philo.data->mtx_print);
}

int	ft_check_arg(t_share *argument)
{
	if (argument->num_of_philo <= 0 || argument->num_of_philo > 200
		|| argument->time_to_die < 60 || argument->time_to_eat < 60
		|| argument->time_to_sleep < 60 || ft_limit(argument))
	{
		ft_put_error("Error: This input is not allowed.\n");
		return (0);
	}
	return (1);
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
		argument.philo_eat_limit = 100000000;
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
	pthread_mutex_destroy(&argument.mtx_end);
	i = 0;
	while (argument.num_of_philo > i)
		pthread_mutex_destroy(&argument.forks[i++].mutex);
	free(philosophers);
	free(argument.forks);
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
