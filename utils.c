/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:58:03 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/27 15:58:08 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						minus;
	signed long long int	number;

	i = 0;
	minus = 0;
	number = 0;
	while ((str[i] == 32 || (str[i] > 8 && str[i] < 14)) && str[i])
		i++;
	if ((str[i] == 45 || str[i] == 43) && str[i])
	{
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) && str[i] != '\0')
	{
		number = (number * 10 + (str[i] - 48));
		i++;
	}
	if (number > 2147483647)
		return (-1);
	return (ft_minus(number, minus));
}

void	add_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

void	rec_itoa(long nb, char *result)
{
	if (nb >= 10)
	{
		rec_itoa(nb / 10, result);
	}
	add_char((nb % 10 + 48), result);
}

int	ft_getlen(int nbr)
{
	int	nbrmalloc;

	nbrmalloc = 1;
	while (nbr >= 10 || nbr <= -10)
	{
		nbr = nbr / 10;
		nbrmalloc++;
	}
	return (nbrmalloc);
}

char	*ft_itoa(int nbr)
{
	int long	nb;
	char		*result;

	if (nbr < 0)
		result = malloc(sizeof(char) * ft_getlen(nbr) + 2);
	else
		result = malloc(sizeof(char) * ft_getlen(nbr) + 1);
	if (!result)
		return (0);
	*result = '\0';
	nb = (long)nbr;
	if (nb < 0)
	{
		nb = nb * -1;
		add_char('-', result);
	}
	rec_itoa(nb, result);
	return (result);
}
