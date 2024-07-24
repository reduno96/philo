/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:16:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/24 12:16:19 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_not_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' && av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_start_threads(char **av)
{
	t_philosopher	*philosophers;
	t_share			argument;

	philosophers = NULL;
	if (ft_is_not_digit(av))
		return ;
	ft_initialize_argument(&argument, av);
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
	ft_cleaning(&argument, philosophers);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
		ft_start_threads(av);
	else
		ft_put_error("The argument not allowed\n");
	return (0);
}
