/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:56:30 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/24 12:17:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM_EATING 2147483647

typedef struct s_fork
{
	int				right_fork;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_share
{
	size_t			creation_time;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				philo_eat_limit;
	int				time_to_sleep;
	int				limit;
	int				end;
	t_fork			*forks;
	pthread_mutex_t	mtx_end;
	pthread_mutex_t	mtx_print;
}					t_share;

typedef struct s_philosopher
{
	int				id;
	int				j;
	int				think;
	int				eating;
	pthread_t		theard;
	t_share			*data;
	size_t			last_meal;
	pthread_mutex_t	mtx_time;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_last;
}					t_philosopher;

int					ft_get_eating(t_philosopher *philo);
void				ft_put_error(char *s);
void				ft_print_actions(t_philosopher *philo, char action);
int					ft_get_end_value(t_philosopher *philo);
void				ft_change_end_value(t_philosopher *philo);
size_t				ft_get_last_meal(t_philosopher *philo);
void				ft_initialize_data(t_philosopher *philo, t_share *argument);
void				ft_initialize_value(t_philosopher *philo);
void				ft_start_threads(char **av);
void				ft_cleaning(t_share *argument, t_philosopher *philosophers);
int					ft_check_arg(t_share *argument);
void				ft_grab_forks(t_philosopher *philo);
void				eating(t_philosopher *philosopher);
void				thinking(t_philosopher *philosopher);
void				sleeping(t_philosopher *philosopher);
void				ft_usleep_to_eat(t_philosopher *philo);
int					ft_usleep(size_t milliseconds);
int					ft_atoi(const char *str);
size_t				ft_get_time(void);
size_t				get_time_passed(t_philosopher *philo, size_t time);
size_t				ft_get_time(void);
void				ft_print_died(t_philosopher philo);
int					is_die(t_philosopher *philo);
void				create_philos(t_philosopher *philo);
void				create_one_philo(t_philosopher *philo);
void				ft_initialize_argument(t_share *argument, char **av);
int					ft_limit(t_share *philo);

#endif
