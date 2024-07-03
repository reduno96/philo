#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_check
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			philo_eat_limit;
	int			time_to_sleep;
}				t_check;

typedef struct s_philosopher
{
	pthread_t	theard;

	int			id;
	int			left_fork;
	int			right_fork;
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			philo_eat_limit;
	t_check		data;
	int			semaphore;
	int			think;
	int			eat;
}				t_philosopher;

void			ft_put_error(char *s);
void			thinking(t_philosopher *philosopher);
void			eating(t_philosopher *philosopher);
void			sleeping(t_philosopher *philosopher);
int				ft_atoi(const char *str);

#endif