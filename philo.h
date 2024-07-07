#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	mutex_right_f;
	pthread_mutex_t	mutex_left_f;
}					t_fork;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				philo_eat_limit;
	int				time_to_sleep;
	int				end;
	t_fork			fork;
}					t_info;

typedef struct s_philosopher
{
	pthread_t		theard;
	int				id;
	t_info			*data;
	long long		creation_time;
	int				think;
	int				eating;
	size_t			last_meal;
}					t_philosopher;

void				ft_put_error(char *s);
void				thinking(t_philosopher *philosopher);
void				eating(t_philosopher *philosopher);
void				sleeping(t_philosopher *philosopher);
int					ft_atoi(const char *str);
long long			ft_get_time(void);
long long			ft_time_passed(long long time);
long long			ft_get_time(void);

#endif