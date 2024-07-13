/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/13 18:33:35 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_to_die(t_philosopher *philo)
{
	if ((get_time_passed(philo->last_meal) > philo->data->time_to_die))
		return (1);
	return (0);
}

int	ft_usleep_to_eat(t_philosopher *philo)
{
	long long	time;

	time = get_time_passed(philo->last_meal);
	// printf("time to last meal %lld\n", time);
	// printf("time to last meal %lld\n", time);
	while (time < philo->data->time_to_eat)
	{
		if (ft_time_to_die(philo))
		{
			// printf("Hi  I'm Here in time to die condition \n");
			return (1);
		}
		time = get_time_passed(philo->last_meal);
	}
	return (0);
}

int	eating(t_philosopher *philo)
{
	ft_grab_forks(philo);
	ft_print_actions(philo, 'E');
	philo->eating++;
	philo->last_meal = ft_get_time();
	if (ft_get_end_value(philo) == 1 && (ft_usleep_to_eat(philo)
			|| ft_time_to_die(philo)))
	{
		ft_change_end_value(philo);
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

int	thinking(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'T');
		return (0);
	}
	return (1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'S');
		ft_usleep(philo->data->time_to_sleep);
		return (0);
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/12 17:58:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_to_die(t_philosopher *philo)
{
	if ((get_time_passed(philo->last_meal) > philo->data->time_to_die))
		return (1);
	return (0);
}

int	ft_usleep_to_eat(t_philosopher *philo)
{
	long long	time;

	time = get_time_passed(philo->last_meal);
	// printf("time to last meal %lld\n", time);
	// printf("time to last meal %lld\n", time);
	while (time < philo->data->time_to_eat)
	{
		if (ft_time_to_die(philo))
		{
			// printf("Hi  I'm Here in time to die condition \n");
			return (1);
		}
		time = get_time_passed(philo->last_meal);
	}
	return (0);
}

int	eating(t_philosopher *philo)
{
	ft_grab_forks(philo);
	ft_print_actions(philo, 'E');
	philo->eating++;
	philo->last_meal = ft_get_time();
	if (ft_get_end_value(philo) == 1 && (ft_usleep_to_eat(philo)
			|| ft_time_to_die(philo)))
	{
		ft_change_end_value(philo);
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

int	thinking(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'T');
		return (0);
	}
	return (1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	if (ft_get_end_value(philo) == 1)
	{
		ft_print_actions(philo, 'S');
		ft_usleep(philo->data->time_to_sleep);
		return (0);
	}
	return (1);
}
