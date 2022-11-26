/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:02:07 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:08:10 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_die(pthread_mutex_t *mutex, t_list *listptr)
{
	print_message(mutex, listptr, 3);
	if (!my_wait(listptr->time_to_sleep, mutex, listptr))
		return (0);
	print_message(mutex, listptr, 4);
	pthread_mutex_lock(&mutex[2]);
	if (*listptr->die == 1)
	{
		pthread_mutex_unlock(&mutex[2]);
		return (0);
	}
	pthread_mutex_unlock(&mutex[2]);
	return (1);
}

int	inside_take_forkeven(pthread_mutex_t *mutex, t_list *listptr)
{
	pthread_mutex_lock(&listptr->mutualex);
	print_message(mutex, listptr, 1);
	pthread_mutex_lock(&listptr->next->mutualex);
	print_message(mutex, listptr, 1);
	print_message(mutex, listptr, 2);
	pthread_mutex_lock(&mutex[1]);
	listptr->end = timestamp(1);
	pthread_mutex_unlock(&mutex[1]);
	if (!my_wait(listptr->time_to_eat, mutex, listptr))
	{
		pthread_mutex_unlock(&listptr->mutualex);
		pthread_mutex_unlock(&listptr->next->mutualex);
		return (0);
	}
	pthread_mutex_unlock(&listptr->next->mutualex);
	pthread_mutex_unlock(&listptr->mutualex);
	if (!is_someone_die(mutex, listptr))
		return (0);
	return (1);
}

int	inside_take_forkodd(pthread_mutex_t *mutex, t_list *listptr)
{
	pthread_mutex_lock(&listptr->next->mutualex);
	print_message(mutex, listptr, 1);
	pthread_mutex_lock(&listptr->mutualex);
	print_message(mutex, listptr, 1);
	print_message(mutex, listptr, 2);
	pthread_mutex_lock(&mutex[1]);
	listptr->end = timestamp(1);
	pthread_mutex_unlock(&mutex[1]);
	if (!my_wait(listptr->time_to_eat, mutex, listptr))
	{
		pthread_mutex_unlock(&listptr->mutualex);
		pthread_mutex_unlock(&listptr->next->mutualex);
		return (0);
	}
	pthread_mutex_unlock(&listptr->mutualex);
	pthread_mutex_unlock(&listptr->next->mutualex);
	if (!is_someone_die(mutex, listptr))
		return (0);
	return (1);
}

void	take_fork(pthread_mutex_t *mutex, t_list *listptr)
{
	int	a;

	a = 0;
	if (listptr->meal > 0)
		a = 1;
	while (42)
	{
		if (listptr->philosopher % 2 == 0)
			if (!inside_take_forkeven(mutex, listptr))
				break ;
		if (listptr->philosopher % 2 == 1)
			if (!inside_take_forkodd(mutex, listptr))
				break ;
		if (a == 1)
		{
			if (!meal_count(listptr))
				return ;
		}
		usleep(10);
	}
}

void	*routine(void *ptr)
{
	t_list	*listptr;

	listptr = (t_list *)ptr;
	pthread_mutex_lock(&listptr->mutex[1]);
	listptr->end = timestamp(1);
	pthread_mutex_unlock(&listptr->mutex[1]);
	listptr->end = 1;
	if (listptr->number_of_philosophers == 1)
	{
		print_message(listptr->mutex, listptr, 1);
		usleep(listptr->time_to_die);
		print_message(listptr->mutex, listptr, 5);
		return (NULL);
	}
	take_fork(listptr->mutex, listptr);
	return (NULL);
}
