/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:43:55 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:08:21 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_destruction(pthread_t *thread, int i)
{
	while (i-- > 0)
	{
		pthread_detach(thread[i]);
		i--;
	}
	return (1);
}

int	thread_wait(pthread_t *thread, int a, pthread_t *la_muerta)
{
	int	i;

	i = 0;
	if (a > 1)
		pthread_join(*la_muerta, NULL);
	while (i < a)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (1);
}

int	inside_death(t_list *listptr, int *count)
{
	if (listptr->end == -42)
			*count = *count + 1;
	pthread_mutex_unlock(&listptr->mutex[1]);
	pthread_mutex_lock(&listptr->mutex[2]);
	if (*listptr->die == 1)
	{
		pthread_mutex_unlock(&listptr->mutex[2]);
		return (0);
	}
	pthread_mutex_unlock(&listptr->mutex[2]);
	usleep(10);
	listptr = listptr->next;
	return (1);
}

void	*death(void *ptr)
{
	t_list	*listptr;
	int		count;

	listptr = (t_list *)ptr;
	count = 0;
	while (count <= listptr->number_of_philosophers)
	{
		pthread_mutex_lock(&listptr->mutex[1]);
		if (listptr->end != -42)
		{
			if (((long int)timestamp(1) - listptr->end)
				> listptr->time_to_die / 1000)
			{
				pthread_mutex_unlock(&listptr->mutex[1]);
				print_message(listptr->mutex, listptr, 5);
				pthread_mutex_lock(&listptr->mutex[2]);
				*listptr->die = 1;
				pthread_mutex_unlock(&listptr->mutex[2]);
				return (NULL);
			}
		}
		if (!inside_death(listptr, &count))
			return (NULL);
	}			
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
