/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:32:43 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/16 15:55:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (ft_get_end_value(philo) == 1)
	{
		if (philo->eating < philo->data->philo_eat_limit)
		{
			if (eating(philo))
				break ;
			if (thinking(philo))
				break ;
			if (sleeping(philo))
				break ;
		}
		else
			break ;
	}
	return (NULL);
}

void	ft_monitor(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == philo->data->num_of_philo)
			i = 0;
		if ((get_time_passed(philo,
					philo->last_meal) >= philo->data->time_to_die))
		{
			ft_print_died(philo[i]);
			break ;
		}
		// if (philo[i].eating < philo->data->philo_eat_limit)
		// 	ft_change_end_value(philo);
		i++;
	}
}
void	create_philos(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		if (pthread_create(&philo[i].theard, NULL, &routine, &philo[i]) != 0)
		{
			ft_put_error("Failed to Create The Theard");
			return ;
		}
		i++;
	}
	ft_monitor(philo);
	i = 0;
	while (i < philo->data->num_of_philo)
	{
		if (pthread_join(philo[i].theard, NULL) != 0)
		{
			ft_put_error("Failed To Join Thread");
			return ;
		}
		i++;
	}
}

void	*routine_one_philo(void *arg)
{
	t_philosopher	*philo;

	(void)arg;
	philo = (t_philosopher *)arg;
	ft_print_actions(philo, 'R');
	ft_usleep(philo->data->time_to_eat);
	printf("\033[31m%lld %d died\033[0m\n", get_time_passed(philo,
			philo->data->creation_time), philo->id);
	return (NULL);
}

void	create_one_philo(t_philosopher *philo)
{
	if (pthread_create(&philo->theard, NULL, routine_one_philo, philo) != 0)
	{
		ft_put_error("Failed to Create The Theard");
		return ;
	}
	if (pthread_join(philo->theard, NULL) != 0)
	{
		ft_put_error("Failed To Join Thread");
		return ;
	}
}
