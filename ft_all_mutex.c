/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:58:39 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/18 18:24:27 by rel-mora         ###   ########.fr       */
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

// void	ft_change_last_meal(t_philosopher *philo)
// {
// 	pthread_mutex_lock(&philo->mtx_last);
// 	philo->last_meal = 0;
// 	pthread_mutex_unlock(&philo->mtx_last);
// }


