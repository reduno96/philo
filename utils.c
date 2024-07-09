/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:05:11 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/09 08:37:24 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

void	ft_grab_forks(t_philosopher *philo)
{
	usleep(100);
	pthread_mutex_lock(&philo->data->forks[philo->j].mutex);
	pthread_mutex_lock(&philo->data->forks[(philo->j + 1)
		% philo->data->num_of_philo].mutex);
	ft_print_actions(philo, 'G');
}

long long	ft_get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

long long	get_time_passed(long long time)
{
	return (ft_get_time() - time);
}
