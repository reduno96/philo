/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/07 18:18:25 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_actions(t_philosopher *philo, char action)
{
	if (action == 'T')
		printf("\e[4;36m Philosopher %d is thinking.\n", philo->id);
}

void	thinking(t_philosopher *philo)
{
	ft_print_actions(philo, 'T');
}

void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->fork.mutex_left_f);
	pthread_mutex_lock(&philo->data->fork.mutex_right_f);
	printf("\e[0;32m Philosopher %d has taken a fork right is %d .\n",
		philo->id, philo->data->fork.right_fork);
	printf("\e[1;33m Philosopher %d has taken a fork left is %d .\n", philo->id,
		philo->data->fork.left_fork);
	philo->eating++;
	printf(" \033[0;91mPhilosopher %d is a eating.\n", philo->id);
	pthread_mutex_unlock(&philo->data->fork.mutex_right_f);
	pthread_mutex_unlock(&philo->data->fork.mutex_left_f);
	printf("\e[0;34m Philosopher %d has finished eating.\n", philo->id);
	// philo->last_meal = ft_get_time();
	// if (ft_time_passed(philo->last_meal) <= philo->data->time_to_eat)
	// {
	// 	printf("\e[0;31m Philosopher %d died.\n", philo->id);
	// 	philo->data->end = 0;
	// 	return ;
	// }
	usleep(philo->data->time_to_eat * 1000);
}

void	sleeping(t_philosopher *philo)
{
	printf("\e[0;30m Philosopher %d is sleeping.\n", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}
