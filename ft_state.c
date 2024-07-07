/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/07 14:14:01 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philosopher *philo)
{
	if (philo->fork.right_fork % 2 == 0)
	{
		philo->think++;
		printf("Philosopher %d is a thinkingis .\n", philo->id);
	}
	usleep(200000);
}

void	eating(t_philosopher *philo)
{
	if (philo->fork.left_fork < philo->fork.right_fork)
	{
		pthread_mutex_lock(&philo->fork.mutex_left_f);
		pthread_mutex_lock(&philo->fork.mutex_right_f);
	}
	else
	{
		pthread_mutex_lock(&philo->fork.mutex_right_f);
		pthread_mutex_lock(&philo->fork.mutex_left_f);
	}
	printf("\e[0;32m Philosopher %d has taken a fork right is %d .\n",
		philo->id, philo->fork.right_fork);
	printf("\e[1;33m Philosopher %d has taken a fork left is %d .\n", philo->id,
		philo->fork.left_fork);
	philo->eating++;
	printf(" \033[0;91mPhilosopher %d is a eating.\n", philo->id);
	pthread_mutex_unlock(&philo->fork.mutex_right_f);
	pthread_mutex_unlock(&philo->fork.mutex_left_f);
	philo->last_meal = ft_get_time();
	if (philo->eating == philo->data->philo_eat_limit)
		philo->data->end = 0;
	usleep(philo->data->time_to_eat * 1000);
}

void	sleeping(t_philosopher *philo)
{
	printf("\e[0;30m Philosopher %d is sleeping.\n", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}
