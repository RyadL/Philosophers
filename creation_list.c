/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:01:47 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:07:53 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*build_list(t_list *listptr, t_list *first, int a, char **argv)
{
	int	i;

	i = 1;
	while (i < a)
	{	
		listptr = add_link(listptr, first, argv);
		if (!listptr)
		{
			free_list(listptr, i - 1);
			return (0);
		}
		if (pthread_mutex_init(&listptr->mutualex, NULL))
		{
			free_list(listptr, i);
			return (0);
		}
		i++;
	}
	return (listptr);
}

t_list	*initiate_list(t_list **firstptr, char **argv,
		pthread_mutex_t *mutex, int *die)
{
	t_list	*first_elementptr;

	first_elementptr = malloc(sizeof(t_list));
	if (!first_elementptr)
		return (0);
	*firstptr = first_elementptr;
	first_elementptr->die = die;
	*first_elementptr->die = 0;
	first_elementptr->mutex = mutex;
	first_elementptr->philosopher = 1;
	first_elementptr->next = first_elementptr;
	first_elementptr->prev = first_elementptr;
	first_elementptr->number_of_philosophers = ft_atoi(argv[1]);
	first_elementptr->time_to_die = ft_atoi(argv[2]) * 1000;
	first_elementptr->time_to_eat = ft_atoi(argv[3]) * 1000;
	first_elementptr->time_to_sleep = ft_atoi(argv[4]) * 1000;
	first_elementptr->meal = 0;
	if (pthread_mutex_init(&(first_elementptr->mutualex), NULL))
	{
		free(first_elementptr);
		return (0);
	}
	if (argv[5])
		first_elementptr->meal = ft_atoi(argv[5]);
	return (first_elementptr);
}

t_list	*add_link(t_list *listptr, t_list *firstptr, char **argv)
{
	static int	number = 2;
	t_list		*new_elementptr;

	new_elementptr = malloc(sizeof(t_list));
	if (!new_elementptr)
		return (0);
	new_elementptr->philosopher = number;
	new_elementptr->next = firstptr;
	new_elementptr->prev = listptr;
	new_elementptr->die = listptr->die;
	new_elementptr->mutex = listptr->mutex;
	new_elementptr->number_of_philosophers = ft_atoi(argv[1]);
	new_elementptr->time_to_die = ft_atoi(argv[2]) * 1000;
	new_elementptr->time_to_eat = ft_atoi(argv[3]) * 1000;
	new_elementptr->time_to_sleep = ft_atoi(argv[4]) * 1000;
	new_elementptr->meal = 0;
	if (argv[5])
		new_elementptr->meal = ft_atoi(argv[5]);
	firstptr->prev = new_elementptr;
	listptr->next = new_elementptr;
	number++;
	return (new_elementptr);
}

void	free_list(t_list *listptr, int lengh)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (i < lengh)
	{
		pthread_mutex_destroy(&listptr->mutualex);
		temp = listptr;
		listptr = listptr->next;
		free(temp);
		i++;
	}
}
