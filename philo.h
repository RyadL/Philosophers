/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:02:29 by rlanani           #+#    #+#             */
/*   Updated: 2022/07/21 16:08:48 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

typedef struct list
{
	int				philosopher;
	struct list		*next;
	struct list		*prev;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutualex;
	int				meal;
	long int		end;
	int				*die;
}	t_list;

//PHILO
int			thread_creation(pthread_t *thread, t_list *listptr,
				pthread_t *la_muerta);
int			thread_wait(pthread_t *thread, int i, pthread_t *la_muerta);
void		print_message(pthread_mutex_t *mutex, t_list *listptr, int message);
void		*death(void *ptr);
int			inside_death(t_list *listptr, int *count);

//CREATION_MUTEX
void		*routine(void *ptr);
void		take_fork(pthread_mutex_t *mutex, t_list *listptr);
void		*death(void *ptr);

//CREATION_LISTS
t_list		*build_list(t_list *listptr, t_list *first, int i, char **argv);
t_list		*initiate_list(t_list **firstptr, char **argv,
				pthread_mutex_t *mutex, int *die);
t_list		*add_link(t_list *listptr, t_list *firstptr, char **argv);
void		free_list(t_list *listptr, int lengh);

//CREATION_MUTEX

void		destroy_mutex(pthread_mutex_t *mutex, int lenght);

long int	timestamp(int i);
int			ft_atoi(const char *str);
int			ft_minus(signed long long int number, int minus);
int			ft_isdigit(int c);
int			launch(int i, t_list *listptr);
int			initiate_mutex(pthread_mutex_t *mutex, int lenght);
void		cleaning(pthread_t *thread, pthread_mutex_t *mutex,
				int *die, t_list *listptr);
int			thread_destruction(pthread_t *thread, int i);
int			my_wait(long int wait, pthread_mutex_t *mutex, t_list *listptr);
int			meal_count(t_list *listptr);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(const char *s);
char		*ft_itoa(int nbr);

#endif
