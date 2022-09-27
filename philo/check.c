/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:59:27 by vasargsy          #+#    #+#             */
/*   Updated: 2022/09/26 13:51:26 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end(t_definit *data)
{
	int	i;

	i = 0;
	while (i < data->include.philo_num)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		pthread_mutex_destroy(data->philo[i].right);
		pthread_mutex_destroy(data->philo[i].left);
		pthread_mutex_destroy(data->philo[i].write);
		i++;
	}
	pthread_mutex_destroy(data->write);
}

int	philo_min_eat(t_definit *data)
{
	int	i;

	i = 0;
	while (i < data->include.philo_num)
	{
		if (data->include.min_count_eat == 0
			|| data->philo[i].eat_count < data->include.min_count_eat)
			return (0);
		i++;
	}
	return (1);
}

void	check_died(t_definit *data)
{
	int	i;

	while (1)
	{
		if (philo_min_eat(data))
		{
			ft_usleep(10);
			printf("%s\n", "OK");
			return ;
		}
		i = 0;
		while (i < data->include.philo_num)
		{
			if (now() - data->philo[i].time > data->include.time_to_die)
			{
				print_action("Died", &data->philo[i]);
				return ;
			}
			i++;
		}
	}
}

void	*eating_start(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	p->time = now();
	if (p->index % 2 == 0)
		eat(p);
	else
	{
		ft_usleep(p->include_.time_to_eat);
		eat(p);
	}
	return (0);
}
