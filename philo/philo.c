/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:01:38 by vasargsy          #+#    #+#             */
/*   Updated: 2022/09/23 18:30:33 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_definit	*data;

	data = malloc(sizeof(t_definit));
	if (!data)
		return (1);
	if (!init_param(data, argc, argv))
		return (2);
	if ((!mutex_create(data)) || (!philo_create(data))
		|| (!thread_create(data)))
		return (3);
	check_died(data);
	end(data);
	return (0);
}
