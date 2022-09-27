/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:43:20 by vasargsy          #+#    #+#             */
/*   Updated: 2022/09/23 14:11:07 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int					philo_num;
	int					time_to_sleep;
	unsigned long long	time_to_die;
	int					time_to_eat;
	int					min_count_eat;
}						t_param;

typedef struct s_philo
{
	t_param				include_;

	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	pthread_mutex_t		*write;

	int					eat_count;
	int					index;

	unsigned long long	time;
	unsigned long long	time_create;
}						t_philo;

typedef struct s_definit
{
	t_param			include;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_t		*thread;
	pthread_mutex_t	*write;
}					t_definit;

int					ft_atoi(const char *str);
int					init_param(t_definit *data, int argc, char **argv);
int					thread_create(t_definit *data);
int					mutex_create(t_definit *data);
void				fill_fork(t_definit *p, int index);
int					philo_create(t_definit *data);
unsigned long long	now(void);
void				*eating_start(void *philo);
void				ft_usleep(unsigned long long time_to_smth);
void				eat(t_philo *p);
void				print_action(char *str, t_philo *p);
void				check_died(t_definit *data);
void				end(t_definit *data);

#endif
