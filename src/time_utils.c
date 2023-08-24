/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:07 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/12 15:53:15 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>

int	get_time_ms(long *const time)
{
	struct timeval	now;

	if (gettimeofday(&now, 0) == 0)
	{
		*time = now.tv_sec * 1000 + now.tv_usec / 1000;
		return (0);
	}
	return (1);
}

