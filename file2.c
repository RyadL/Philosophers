/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:23:51 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:23:54 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_message(t_list *listptr, int message)
{
	char	*string;
	char	*string2;

	string = (ft_strjoin(ft_itoa((int)timestamp(1)), " "));
	string2 = ft_itoa(listptr->philosopher);
	string = (ft_strjoin(string, string2));
	free(string2);
	if (message == 1)
		string = (ft_strjoin(string, " has taken a fork\n"));
	if (message == 2)
		string = (ft_strjoin(string, " is eating\n"));
	if (message == 3)
		string = (ft_strjoin(string, " is sleeping\n"));
	if (message == 4)
		string = (ft_strjoin(string, " is thinking\n"));
	if (message == 5)
		string = (ft_strjoin(string, " died\n"));
	return (string);
}

void	print_message(pthread_mutex_t *mutex, t_list *listptr, int message)
{
	char	*string;

	pthread_mutex_lock(&mutex[0]);
	pthread_mutex_lock(&mutex[2]);
	string = ft_message(listptr, message);
	if (*listptr->die != 1)
		write(1, string, ft_strlen(string));
	free(string);
	pthread_mutex_unlock(&mutex[2]);
	pthread_mutex_unlock(&mutex[0]);
	return ;
}

int	thread_creation(pthread_t *thread, t_list *listptr, pthread_t *la_muerta)
{
	int	i;

	i = 0;
	while (i < listptr->number_of_philosophers)
	{
		if (pthread_create (&thread[i], NULL, routine, listptr))
		{
			pthread_mutex_lock(&listptr->mutex[2]);
			*listptr->die = 1;
			pthread_mutex_unlock(&listptr->mutex [2]);
			thread_wait(thread, i, la_muerta);
			return (0);
		}
		listptr = listptr->next;
		i++;
	}
	if (listptr->number_of_philosophers > 1)
	{
		usleep(1000);
		pthread_create (la_muerta, NULL, death, listptr);
	}
	return (1);
}
