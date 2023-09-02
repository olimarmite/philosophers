/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stopable_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 00:32:01 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/03 00:44:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "settings.h"
#include <unistd.h>

#if USE_STOPABLE_SLEEP

void	stopable_sleep(__useconds_t time, t_shared_ressource *shared_ressource)
{
	__useconds_t	remaining;
	__useconds_t	loop_time;

	loop_time = time / STOPABLE_SLEEP_LOOP_INTERVAL;
	remaining = time % STOPABLE_SLEEP_LOOP_INTERVAL;
	while (loop_time > 0)
	{
		if (shared_ressource->is_terminated == 0)
			usleep(STOPABLE_SLEEP_LOOP_INTERVAL);
		else
			return ;
		--loop_time;
	}
	usleep(remaining);
}

#else

void	stopable_sleep(__useconds_t time, t_shared_ressource *shared_ressource)
{
	(void) shared_ressource;
	usleep(time);
}

#endif
