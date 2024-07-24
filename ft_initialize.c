/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:49:58 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/24 12:06:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initialize_value(t_philosopher *philo)
{
	philo->eating = 0;
	philo->data->end = 1;
}

void	ft_initialize_argument(t_share *argument, char **av)
{
	argument->num_of_philo = ft_atoi(av[1]);
	argument->time_to_die = ft_atoi(av[2]);
	argument->time_to_eat = ft_atoi(av[3]);
	argument->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		argument->philo_eat_limit = ft_atoi(av[5]);
	else
	{
		argument->philo_eat_limit = NUM_EATING;
		argument->limit = -1;
	}
}

void	ft_initialize_data(t_philosopher *philo, t_share *argument)
{
	int	i;

	i = 0;
	argument->forks = malloc(argument->num_of_philo * sizeof(t_fork));
	if (!argument->forks)
		return ;
	argument->creation_time = ft_get_time();
	while (i < argument->num_of_philo)
	{
		philo[i].last_meal = argument->creation_time;
		philo[i].id = i + 1;
		philo[i].j = i;
		argument->forks[i].right_fork = i;
		pthread_mutex_init(&argument->forks[i].mutex, NULL);
		pthread_mutex_init(&philo[i].mtx_time, NULL);
		pthread_mutex_init(&philo[i].mtx_last, NULL);
		pthread_mutex_init(&philo[i].mtx_eat, NULL);
		philo[i].data = argument;
		i++;
	}
	pthread_mutex_init(&argument->mtx_print, NULL);
	pthread_mutex_init(&argument->mtx_end, NULL);
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
