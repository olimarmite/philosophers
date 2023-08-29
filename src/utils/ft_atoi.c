/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 02:55:39 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 20:54:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>


static inline int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

/**
 * Convert String [nptr] formated number to int
 *
 * @param nptr Input String
 * @param nbr Output pointer
 * @return Return 0 if [nptr] is a valid number
 */
int	ft_atoi(const char *nptr, int *nbr)
{
	long	nb;
	size_t	i;

	nb = 0;
	i = 0;
	*nbr = 0;
	if (*nptr == '-' || *nptr == '+')
		i++;
	while ((nptr[i] != 0))
	{
		if (ft_isdigit(nptr[i]) != 1)
			return (1);
		else
		{
			nb = nb * 10 + (nptr[i] - '0');
			if (nb - (*nptr == '-') > INT_MAX)
				return (1);
			i++;
		}
	}
	if (*nptr == '-')
		nb *= -1;
	*nbr = nb;
	return (0);
}
