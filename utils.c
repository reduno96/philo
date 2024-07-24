/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:05:11 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/18 18:27:47 by rel-mora         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->forks[philo->j].mutex);
	ft_print_actions(philo, 'R');
	pthread_mutex_lock(&philo->data->forks[(philo->j + 1)
		% philo->data->num_of_philo].mutex);
	ft_print_actions(philo, 'L');
}

size_t	ft_get_time(void)
{
	struct timeval	time;
	size_t			ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

size_t	get_time_passed(t_philosopher *philo, size_t time)
{
	(void)philo;
	return (ft_get_time() - time);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;
	size_t	end;

	start = ft_get_time();
	end = start + milliseconds;
	while ((ft_get_time()) < end)
		usleep(200);
	return (0);
}
