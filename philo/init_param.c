/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:46:55 by vasargsy          #+#    #+#             */
/*   Updated: 2022/09/26 14:26:46 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(t_definit *data)
{
	int	i;

	i = 0;
	data->thread = malloc(sizeof(pthread_t) * data->include.philo_num);
	if (!data->thread)
		return (0);
	while (i < data->include.philo_num)
	{
		if ((pthread_create(&data->thread[i], NULL,
					eating_start, (void *)&data->philo[i])) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->include.philo_num)
	{
		pthread_detach(data->thread[i]);
		i++;
	}	
	return (1);
}

int	mutex_create(t_definit *data)
{
	int	i;

	i = 0;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->include.philo_num);
	data->write = malloc(sizeof(pthread_mutex_t));
	if (!data->mutex || !data->write)
		return (0);
	pthread_mutex_init(data->write, NULL);
	while (i < data->include.philo_num)
	{
		if ((pthread_mutex_init(&data->mutex[i], NULL)) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	fill_fork(t_definit *p, int index)
{
	int	j;

	if (index == p->include.philo_num - 1)
		j = 0;
	else
		j = index + 1;
	p->philo[index].right = &p->mutex[index];
	p->philo[index].left = &p->mutex[j];
}

int	philo_create(t_definit *data)
{
	int					i;
	unsigned long long	create_time;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->include.philo_num);
	if (!data->philo)
		return (0);
	while (i < data->include.philo_num)
	{
		data->philo[i].include_ = data->include;
		data->philo[i].eat_count = 0;
		data->philo[i].index = i;
		data->philo[i].time_create = now();
		data->philo[i].write = data->write;
		data->philo[i].time = now();
		fill_fork(data, i);
		i++;
	}
	return (1);
}

int	init_param(t_definit *data, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
			|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
			return (0);
		else if (argc == 6 && ft_atoi(argv[5]) <= 0)
			return (0);
		data->include.philo_num = ft_atoi(argv[1]);
		data->include.time_to_die = ft_atoi(argv[2]);
		data->include.time_to_eat = ft_atoi(argv[3]);
		data->include.time_to_sleep = ft_atoi(argv[4]);
		data->include.min_count_eat = 0;
		if (argc == 6)
			data->include.min_count_eat = ft_atoi(argv[5]);
		return (1);
	}
	return (0);
}
