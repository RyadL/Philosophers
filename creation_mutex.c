/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:01:58 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/27 11:14:11 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initiate_mutex(pthread_mutex_t *mutex, int lenght)
{
	int	i;

	i = 0;
	while (i < lenght)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
		{
			destroy_mutex(mutex, i - 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_mutex(pthread_mutex_t *mutex, int lenght)
{
	int	i;

	i = 0;
	while (i < lenght)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

int	my_wait(long int wait, pthread_mutex_t *mutex, t_list *listptr)
{
	while (wait)
	{
		if (wait < 60000)
		{
			usleep(wait);
			break ;
		}
		usleep(60000);
		pthread_mutex_lock(&mutex[2]);
		if (*listptr->die == 1)
		{
			pthread_mutex_unlock(&mutex[2]);
			return (0);
		}
		pthread_mutex_unlock(&mutex[2]);
		wait = wait - 60000;
	}
	return (1);
}

int	meal_count(t_list *listptr)
{
	listptr->meal--;
	if (listptr->meal == 0)
	{
		pthread_mutex_lock(&listptr->mutex[1]);
		listptr->end = -42;
		pthread_mutex_unlock(&listptr->mutex[1]);
		return (0);
	}
	return (1);
}
