/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/18 18:36:18 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_to_die(t_philosopher *philo)
{
	if (is_die(philo))
		return (1);
	return (0);
}

void	ft_usleep_to_eat(t_philosopher *philo)
{
	// size_t	time;

	// time = get_time_passed(philo, philo->last_meal);
	// while (time < (size_t)philo->data->time_to_eat)
	// {
	// 	if (ft_time_to_die(philo))
	// 		ft_change_end_value(philo);
	// 	time = get_time_passed(philo, philo->last_meal);
	// }
	ft_usleep(philo->data->time_to_eat);
}

int	eating(t_philosopher *philo)
{
	ft_grab_forks(philo);
	philo->eating++;
	pthread_mutex_lock(&philo->mtx_last);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->mtx_last);
	ft_usleep_to_eat(philo);
	ft_print_actions(philo, 'E');
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
