/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:07 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 20:08:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdatomic.h>

int	get_time_ms(long *const time)
{
	struct timeval	now;

	if (gettimeofday(&now, 0) == 0)
	{
		*time = now.tv_sec * 1000 + now.tv_usec / 1000;
		return (0);
	}
	*time = 0;
	return (1);
}

int	get_time_from_start_ms(long *const time)
{
	static atomic_long	start_time = -1;
	long				now;

	if (get_time_ms(&now))
		return (1);
	if (start_time == -1)
	{
		start_time = now;
	}
	*time = now - start_time;
	return (0);
}
