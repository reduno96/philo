#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				right_fork;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_share
{
	long long		creation_time;
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
	pthread_mutex_t	mtx_time;
}					t_share;

typedef struct s_philosopher
{
	int				id;
	int				j;
	int				think;
	int				eating;
	long long		last_meal;
	pthread_t		theard;
	t_share			*data;
}					t_philosopher;

void				ft_put_error(char *s);
void				ft_print_actions(t_philosopher *philo, char action);
int					ft_get_end_value(t_philosopher *philo);
void				ft_change_end_value(t_philosopher *philo);
void				ft_grab_forks(t_philosopher *philo);
int					eating(t_philosopher *philosopher);
int					thinking(t_philosopher *philosopher);
int					sleeping(t_philosopher *philosopher);
void				ft_usleep_to_eat(t_philosopher *philo);
int					ft_usleep(size_t milliseconds);
int					ft_atoi(const char *str);
long long			ft_get_time(void);
long long			get_time_passed(t_philosopher *philo, long long time);
long long			ft_get_time(void);
void				ft_print_died(t_philosopher philo);
void				create_philos(t_philosopher *philo);
void				create_one_philo(t_philosopher *philo);

#endif
