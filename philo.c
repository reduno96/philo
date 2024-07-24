/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:00:03 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/24 12:16:41 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_print_died(t_philosopher philo)
{
	pthread_mutex_lock(&philo.data->mtx_print);
	printf("\033[31m%zu %d died\033[0m\n", get_time_passed(&philo,
			philo.data->creation_time), philo.id);
	ft_change_end_value(&philo);
	pthread_mutex_unlock(&philo.data->mtx_print);
}

void	ft_print_actions(t_philosopher *philo, char action)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	if (ft_get_end_value(philo) == 1)
	{
		if (action == 'T')
			printf("%zu %d is thinking\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'R')
			printf("%zu %d has taken a fork\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'L')
			printf("%zu %d has taken a fork\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'E')
			printf("%zu %d is eating\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
		else if (action == 'S')
			printf("%zu %d is sleeping\n", get_time_passed(philo,
					philo->data->creation_time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->mtx_print);
}

void	ft_cleaning(t_share *argument, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&argument->mtx_end);
	pthread_mutex_destroy(&argument->mtx_print);
	i = 0;
	while (argument->num_of_philo > i)
		pthread_mutex_destroy(&argument->forks[i++].mutex);
	i = 0;
	while (argument->num_of_philo > i)
	{
		pthread_mutex_destroy(&philosophers[i].mtx_time);
		pthread_mutex_destroy(&philosophers[i].mtx_eat);
		pthread_mutex_destroy(&philosophers[i].mtx_last);
		i++;
	}
	free(philosophers);
	free(argument->forks);
}
