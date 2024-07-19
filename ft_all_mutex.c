/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:58:39 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/19 19:32:16 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_end_value(t_philosopher *philo)
{
	int	r;

	pthread_mutex_lock(&philo->data->mtx_end);
	r = philo->data->end;
	pthread_mutex_unlock(&philo->data->mtx_end);
	return (r);
}

void	ft_change_end_value(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	philo->data->end = 0;
	pthread_mutex_unlock(&philo->data->mtx_end);
}

size_t	ft_get_last_meal(t_philosopher *philo)
{
	size_t	r;

	pthread_mutex_lock(&philo->mtx_last);
	r = philo->last_meal;
	pthread_mutex_unlock(&philo->mtx_last);
	return (r);
}

// int	is_die(t_philosopher *philo)
// {
// 	pthread_mutex_lock(&philo->mtx_time);
// 	if ((get_time_passed(philo,
// 				ft_get_last_meal(philo)) >= (size_t)philo->data->time_to_die))
// 	{
// 		pthread_mutex_unlock(&philo->mtx_time);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->mtx_time);
// 	return (0);
// }
