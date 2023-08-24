/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heartbeats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:27:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/23 14:08:46 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include "settings.h"

int	heartbeats_init(atomic_long	**heartbeats_array, const t_settings *settings)
{
	_Static_assert(ATOMIC_INT_LOCK_FREE == 2);
	log_info("heartbeats_init", "Init heartbeats array");
	*heartbeats_array = calloc(settings->worker_count,  sizeof(atomic_long));

	if (*heartbeats_array == NULL)
	{
		log_err("heartbeats_init", "Failed to init heartbeats array");
		return (1);
	}
	return (0);
}

int	check_hearbeats(
	const atomic_long	*heartbeats_array,
	const t_settings *settings
	)
{
	int				i;
	long			tmp_time;
	long			now;
	int				missed_hb;

	missed_hb = 0;
	if (get_time_ms(&now))
	{
		return (1);
	}
	i = 0;
	while (i < settings->worker_count)
	{
		tmp_time = heartbeats_array[i];
		if (tmp_time + LIFE_MAX_DURATION < now && tmp_time != 0)
		{
			//log_info("check_hearbeats", "Philo missed an heartbeat");
			printf("----  check_hearbeats: Philo %i missed an heartbeat by %ld ms\n",
				i, now - (tmp_time + LIFE_MAX_DURATION));
			missed_hb = 1;
		}
		++i;
	}
	return (missed_hb);
}

int	monitor_heatbeats(
	const atomic_long	*heartbeats_array,
	const t_settings	*settings
	)
{
	// int	i;

	// i = 0;
	// while (i)
	// {
	// 	check_hearbeats(heartbeats_array, settings);
	// 	usleep(MONITORING_LOOP_INTERVAL);
	// 	++i;
	// }
	while (1)
	{
		if (check_hearbeats(heartbeats_array, settings))
		{
			return (1);
		}
		usleep(MONITORING_LOOP_INTERVAL);
	}
	return (0);
}
