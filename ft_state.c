/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/16 15:39:15 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_to_die(t_philosopher *philo)
{
	if ((get_time_passed(philo, philo->last_meal) >= philo->data->time_to_die))
		return (1);
	return (0);
}

void	ft_usleep_to_eat(t_philosopher *philo)
{
	long long	time;

	time = get_time_passed(philo, philo->last_meal);
	while (time < philo->data->time_to_eat)
	{
		if (ft_time_to_die(philo))
			ft_change_end_value(philo);
		time = get_time_passed(philo, philo->last_meal);
	}
}

int	eating(t_philosopher *philo)
{
	ft_grab_forks(philo);
	ft_print_actions(philo, 'E');
	philo->eating++;
	philo->last_meal = ft_get_time();
	ft_usleep_to_eat(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->j].mutex);
	pthread_mutex_unlock(&philo->data->forks[(philo->j + 1)
		% philo->data->num_of_philo].mutex);
	return (0);
}

int	thinking(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'T');
		return (0);
	}
	return (1);
}

int	sleeping(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'S');
		ft_usleep(philo->data->time_to_sleep);
		return (0);
	}
	return (1);
}
