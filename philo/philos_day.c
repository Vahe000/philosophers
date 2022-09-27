/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_day.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:31:00 by vasargsy          #+#    #+#             */
/*   Updated: 2022/09/27 15:13:14 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_down_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
}

static void	is_sleeping(t_philo *p)
{
	print_action("Is sleeping", p);
	ft_usleep(p->include_.time_to_sleep);
	print_action("Is thinking", p);
}

void	print_action(char *str, t_philo *p)
{
	pthread_mutex_lock(p->write);
	printf("%llu\t%d\t%s\n", now() - p->time_create, p->index + 1, str);
	pthread_mutex_unlock(p->write);
}

static void	philo_takes_fork(t_philo *p)
{
	pthread_mutex_lock(p->right);
	print_action("Has taken right fork", p);
	pthread_mutex_lock(p->left);
	print_action("Has taken left fork", p);
}

void	eat(t_philo *p)
{
	while (1)
	{	
		philo_takes_fork(p);
		print_action("Is eating", p);
		ft_usleep(p->include_.time_to_eat);
		p->time = now();
		p->eat_count++;
		put_down_forks(p);
		is_sleeping(p);
	}
}
