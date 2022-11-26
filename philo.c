/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:02:16 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:08:32 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	inside_main(t_list *listptr, char **argv, pthread_t *thread)
{
	pthread_t	la_muerta;

	if (!listptr)
	{
		cleaning(thread, listptr->mutex, listptr->die, listptr);
		return (0);
	}
	if (!initiate_mutex(listptr->mutex, 3))
	{
		cleaning(thread, listptr->mutex, listptr->die, listptr);
		return (0);
	}
	if (!thread_creation(thread, listptr, &la_muerta))
	{
		destroy_mutex(listptr->mutex, 3);
		return (0);
	}
	thread_wait(thread, ft_atoi(argv[1]), &la_muerta);
	destroy_mutex(listptr->mutex, 3);
	return (1);
}

int	verification_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		printf("invalid arguments\n");
		return (0);
	}
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("invalid arguments\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	cleaning(pthread_t *thread, pthread_mutex_t *mutex,
		int *die, t_list *listptr)
{
	if (thread)
		free(thread);
	if (mutex)
		free(mutex);
	if (thread)
		free(die);
	if (listptr)
		free_list(listptr, listptr->number_of_philosophers);
}

int	is_greater(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_list			*listptr;
	t_list			*firstptr;
	pthread_mutex_t	*mutex;
	int				*die;

	if (!verification_arguments(argc, argv)
		|| (argv[5] && !ft_atoi(argv[5])) || !ft_atoi(argv[1]))
		return (0);
	if (!is_greater(argv))
		return (0);
	thread = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	mutex = malloc(sizeof(pthread_mutex_t) * 3);
	die = malloc(sizeof(int));
	listptr = initiate_list(&firstptr, argv, mutex, die);
	if (!die || !mutex || !thread || !listptr)
	{
		cleaning(thread, mutex, die, listptr);
		return (0);
	}
	timestamp(0);
	listptr = build_list(listptr, firstptr, ft_atoi(argv[1]), argv);
	inside_main(listptr, argv, thread);
	cleaning(thread, mutex, die, listptr);
	return (1);
}
