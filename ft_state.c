/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/09 08:52:34 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_to_die(t_philosopher *philo)
{
	if ((get_time_passed(philo->last_meal) > philo->data->time_to_die))
	{
		pthread_mutex_lock(&philo->data->print);
		ft_print_actions(philo, 'D');
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->forks[philo->j].mutex);
		pthread_mutex_unlock(&philo->data->forks[(philo->j + 1)
			% philo->data->num_of_philo].mutex);
		philo->data->end = 0;
		return (1);
		pthread_mutex_unlock(&philo->data->print);
	}
	return (0);
}

int	ft_usleep_to_eat(t_philosopher *philo)
{
	long long	time;

	time = get_time_passed(philo->last_meal);
	while (time < philo->data->time_to_eat)
	{
		if (ft_time_to_die(philo))
			return (1);
		time = get_time_passed(philo->last_meal);
	}
	return (0);
}

int	eating(t_philosopher *philo)
{
	ft_grab_forks(philo);
	ft_print_actions(philo, 'R');
	ft_print_actions(philo, 'E');
	philo->eating++;
	philo->last_meal = ft_get_time();
	if (ft_usleep_to_eat(philo) || ft_time_to_die(philo))
	{
		ft_print_actions(philo, 'D');
		pthread_mutex_unlock(&philo->data->forks[philo->j].mutex);
		pthread_mutex_unlock(&philo->data->forks[(philo->j + 1)
			% philo->data->num_of_philo].mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->forks[philo->j].mutex);
	pthread_mutex_unlock(&philo->data->forks[(philo->j + 1)
		% philo->data->num_of_philo].mutex);
	return (0);
}

void	thinking(t_philosopher *philo)
{
	ft_print_actions(philo, 'T');
}

void	sleeping(t_philosopher *philo)
{
	ft_print_actions(philo, 'S');
	usleep(philo->data->time_to_sleep * 1000);
}
