/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:34:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/01 00:28:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	if ((size == 0) || (nmemb == 0))
		return (malloc(0));
	if (((nmemb * size) / size != nmemb))
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	while (i < (nmemb * size))
	{
		mem[i] = 0;
		i++;
	}
	memset(mem, 0, nmemb * size);
	return ((void *)(mem));
}
