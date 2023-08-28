/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heartbeats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:27:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:52:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include "settings.h"

int	heartbeats_init(atomic_long	**heartbeats_array, const t_settings *settings)
{
	_Static_assert(ATOMIC_INT_LOCK_FREE == 2,
		"ATOMIC_INT_LOCK_FREE not supported");
	log_info("heartbeats_init", "Init heartbeats array");
	*heartbeats_array = calloc(settings->worker_count, sizeof(atomic_long));
	if (*heartbeats_array == NULL)
	{
		log_err("heartbeats_init", "Failed to init heartbeats array");
		return (1);
	}
	return (0);
}

void	heartbeats_destroy(atomic_long	*heartbeats_array)
{
	free(heartbeats_array);
}

int	check_hearbeats(
	const atomic_long *heartbeats_array,
	const t_settings *settings,
	pthread_mutex_t *display_lock)
{
	int				i;
	long			tmp_time;
	long			now;
	int				missed_hb;
	int				end;

	missed_hb = 0;
	if (get_time_from_start_ms(&now))
		return (1);
	i = 0;
	while (i < settings->worker_count)
	{
		end = 1;
		tmp_time = heartbeats_array[i];
		end = (end && (tmp_time < 0));
		if (tmp_time + LIFE_MAX_DURATION < now && tmp_time > 0)
		{
			pthread_mutex_lock(display_lock);
			printf("----  check_hearbeats: Philo %i missed an heartbeat by %ld ms\n", i, now - (tmp_time + LIFE_MAX_DURATION));
			pthread_mutex_unlock(display_lock);
			missed_hb = 1;
		}
		++i;
	}
	return (missed_hb | end);
}

int	monitor_heatbeats(
	const atomic_long *heartbeats_array,
	const t_settings *settings,
	pthread_mutex_t *display_lock
	)
{
	while (1)
	{
		if (check_hearbeats(heartbeats_array, settings, display_lock))
		{
			return (1);
		}
		usleep(MONITORING_LOOP_INTERVAL);
	}
	return (0);
}
