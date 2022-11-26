/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:12:10 by rlanani           #+#    #+#             */
/*   Updated: 2022/08/08 14:12:12 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timestamp(int i)
{
	long int				timestamp;
	static int				initiate;
	static struct timeval	start;
	struct timeval			checkpoint;

	if (initiate == 0)
	{
		gettimeofday(&start, NULL);
		initiate++;
		return (0);
	}
	gettimeofday(&checkpoint, NULL);
	if (i == 1)
		timestamp = ((checkpoint.tv_sec * 1000) + (checkpoint.tv_usec / 1000))
			- ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	if (i == 0)
		timestamp = checkpoint.tv_usec;
	return (timestamp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*dst;
	int		i;

	if (!(s1) || !(s2))
		return (0);
	i = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dst = malloc(sizeof(char) * (len) +1);
	if (!(dst))
		return (0);
	len = 0;
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	while (len <= ft_strlen(s2))
	{
		dst[i] = s2[len];
		i++;
		len++;
	}
	free(s1);
	return (dst);
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_minus(signed long long int number, int minus)
{
	if (minus % 2 != 0)
	{
		return (-number);
	}
	else
		return (number);
}
