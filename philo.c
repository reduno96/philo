/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:00:03 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/13 20:54:11 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	ft_initialize_value(t_philosopher *philo)
{
	philo->eating = 0;
	philo->last_meal = 0;
	philo->data->end = 1;
}

void	ft_print_actions(t_philosopher *philo, char action)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	if (ft_get_end_value(philo) == 1)
	{
		if (action == 'T')
			printf("%lld %d is thinking\n",
				get_time_passed(philo->creation_time, philo), philo->id);
		else if (action == 'R')
			printf("%lld %d has taken a fork\n",
				get_time_passed(philo->creation_time, philo), philo->id);
		else if (action == 'L')
			printf("%lld %d has taken a fork\n",
				get_time_passed(philo->creation_time, philo), philo->id);
		else if (action == 'E')
			printf("%lld %d is eating\n", get_time_passed(philo->creation_time, philo),
				philo->id);
		else if (action == 'S')
			printf("%lld %d is sleeping\n",
				get_time_passed(philo->creation_time, philo), philo->id);
	}
	pthread_mutex_unlock(&philo->data->mtx_print);
}

int	ft_limit(t_share *philo)
{
	if (philo->limit != -1)
	{
		if (philo->philo_eat_limit <= 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_get_end_value(t_philosopher *philo)
{
	int	r;

	pthread_mutex_lock(&philo->data->mtx_end);
	r = philo->data->end;
	pthread_mutex_unlock(&philo->data->mtx_end);
	return (r);
}

void	ft_change_end_value(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	philo->data->end = 0;
	pthread_mutex_unlock(&philo->data->mtx_end);
}
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0 || philo->id == philo->data->num_of_philo)
		sleeping(philo);
	while (ft_get_end_value(philo) == 1
			/* && philo->eating < philo->data->philo_eat_limit */)
	{
		if (eating(philo))
			break ;
		if (thinking(philo))
			break ;
		if (sleeping(philo))
			break ;
		// printf("get_time_passed %lld\n", get_time_passed(philo->last_meal));
		// if (get_time_passed(philo->last_meal) > philo->data->time_to_die
		// 	|| (philo->data->time_to_eat
		// 		+ philo->data->time_to_sleep) > philo->data->time_to_die)
		// {
		// 	ft_change_end_value(philo);
		// 	break ;
		// }
	}
	return (NULL);
}

void	ft_initialize_data(t_philosopher *philo, t_share *argument)
{
	int	i;

	argument->forks = malloc(argument->num_of_philo * sizeof(t_fork));
	i = 0;
	while (i < argument->num_of_philo)
	{
		philo[i].creation_time = ft_get_time();
		philo[i].id = i + 1;
		philo[i].j = i;
		argument->forks[i].right_fork = i;
		pthread_mutex_init(&argument->forks[i].mutex, NULL);
		philo[i].data = argument;
		i++;
	}
	pthread_mutex_init(&argument->mtx_print, NULL);
	pthread_mutex_init(&argument->mtx_end, NULL);
	pthread_mutex_init(&argument->mtx_get_time, NULL);
}
void	ft_print_died(t_philosopher philo)
{
	printf("%lld %d died\n", get_time_passed(philo.creation_time, philo), philo.id);
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
	i = 0;
	while (1)
	{
		if (i == philo->data->num_of_philo)
			i = 0;
		if (philo->data->end == 0)
		{
			ft_print_died(philo[i]);
			break ;
		}
		i++;
	}
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

	philo = (t_philosopher *)arg;
	while (1)
	{
		printf("%lld %d has taken a fork\n",
			get_time_passed(philo->creation_time, philo), philo->id);
		printf("%lld %d is eating\n", get_time_passed(philo->creation_time, philo),
			philo->id);
		philo->last_meal = ft_get_time();
		if (ft_usleep_to_eat(philo)
			|| get_time_passed(philo->last_meal, philo) > philo->data->time_to_die
			|| (philo->data->time_to_sleep
				+ philo->data->time_to_eat) > philo->data->time_to_die)
		{
			printf("%lld %d died\n", get_time_passed(philo->creation_time, philo),
				philo->id);
			break ;
		}
		printf("%lld %d is thinking\n", get_time_passed(philo->creation_time, philo),
			philo->id);
		printf("%lld %d is sleeping\n", get_time_passed(philo->creation_time,  philo),
			philo->id);
		ft_usleep(philo->data->time_to_sleep );
	}
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

int	ft_check_arg(t_share *argument)
{
	if (argument->num_of_philo <= 0 || argument->num_of_philo > 200
		|| argument->time_to_die < 60 || argument->time_to_eat < 60
		|| argument->time_to_sleep < 60 || ft_limit(argument))
	{
		ft_put_error("Error: This input is not allowed.\n");
		return (0);
	}
	return (1);
}
void	ft_start_threads(char **av)
{
	t_philosopher	*philosophers;
	t_share			argument;
	int				i;

	philosophers = NULL;
	argument.num_of_philo = ft_atoi(av[1]);
	argument.time_to_die = ft_atoi(av[2]);
	argument.time_to_eat = ft_atoi(av[3]);
	argument.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		argument.philo_eat_limit = ft_atoi(av[5]);
	else
	{
		argument.philo_eat_limit = 100000000;
		argument.limit = -1;
	}
	if (!ft_check_arg(&argument))
		return ;
	philosophers = malloc(argument.num_of_philo * sizeof(t_philosopher));
	if (!philosophers)
		return ;
	ft_initialize_data(philosophers, &argument);
	ft_initialize_value(philosophers);
	if (philosophers->data->num_of_philo == 1)
		create_one_philo(philosophers);
	else
		create_philos(philosophers);
	pthread_mutex_destroy(&argument.mtx_end);
	i = 0;
	while (argument.num_of_philo > i)
		pthread_mutex_destroy(&argument.forks[i++].mutex);
	free(philosophers);
	free(argument.forks);
}
int	main(int ac, char **av)
{
	(void)ac;
	if (ac == 5 || ac == 6)
		ft_start_threads(av);
	else
		ft_put_error("The argument not allowed\n");
	return (0);
}
