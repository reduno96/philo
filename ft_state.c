/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/03 16:20:51 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		// printf("Philosopher is thinking philosopher->time %d is .\n", philo->id);
		philo->think++;
		// printf("%d\n", philo->think);
		printf("*************think-> %d is .\n", philo->think);

	}

		usleep(200000);
}

void	eating(t_philosopher *philosopher)
{
	printf("Philosopher %d is eating.\n", philosopher->id);
	usleep(200000);
}

void	sleeping(t_philosopher *philosopher)
{
	printf("Philosopher %d is sleeping.\n", philosopher->id);
	usleep(100000);
}


