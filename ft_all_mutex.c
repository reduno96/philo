/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:58:39 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/16 13:59:42 by rel-mora         ###   ########.fr       */
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
