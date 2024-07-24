/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/24 10:21:13 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep_to_eat(t_philosopher *philo)
{
	ft_usleep(philo->data->time_to_eat);
}

void	eating(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_grab_forks(philo);
		pthread_mutex_lock(&philo->mtx_last);
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(&philo->mtx_last);
		ft_print_actions(philo, 'E');
		ft_usleep_to_eat(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->j].mutex);
		pthread_mutex_unlock(&philo->data->forks[(philo->j + 1)
			% philo->data->num_of_philo].mutex);
	}
}

void	thinking(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'T');
	}
}

void	sleeping(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'S');
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	ft_put_error(char *s)
{
	printf("%s", s);
}
