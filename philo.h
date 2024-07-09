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
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				philo_eat_limit;
	int				time_to_sleep;
	int				limit;
	int				end;
	t_fork			*forks;
	pthread_mutex_t	print;
}					t_share;

typedef struct s_philosopher
{
	long long		creation_time;
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
void				ft_grab_forks(t_philosopher *philo);
int					eating(t_philosopher *philosopher);
void				thinking(t_philosopher *philosopher);
void				sleeping(t_philosopher *philosopher);
int					ft_usleep_to_eat(t_philosopher *philo);
int					ft_atoi(const char *str);
long long			ft_get_time(void);
long long			get_time_passed(long long time);
long long			ft_get_time(void);

#endif