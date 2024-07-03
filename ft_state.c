/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/06/29 20:24:18 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philosopher *philosopher)
{
	if (philosopher->right_fork % 2 == 0)
	{
		printf("Philosopher %d is thinking philosopher->time %d is .\n",
			philosopher->time_to_eat, philosopher->id);
		printf("philosopher->time %d is .\n", philosopher->time_to_eat);
		usleep(philosopher->time_to_eat);
	}
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
