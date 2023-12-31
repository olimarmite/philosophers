/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heartbeats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:27:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/03 00:16:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include "settings.h"
#include <string.h>

int	heartbeats_init(
	t_heartbeat_entry	**heartbeats_array,
	const t_settings *settings)
{
	int	i;

	log_info("heartbeats_init", "init heartbeats array", NULL);
	*heartbeats_array = ft_calloc(
			settings->worker_count, sizeof(t_heartbeat_entry));
	if (*heartbeats_array == NULL)
	{
		log_err("heartbeats_init", "Failed to init heartbeats array", NULL);
		return (1);
	}
	i = 0;
	while (i < settings->worker_count)
	{
		if (pthread_mutex_init(&((*heartbeats_array)[i].lock), NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&((*heartbeats_array)[i].lock));
			}
			free(*heartbeats_array);
			return (0);
		}
		++i;
	}
	return (0);
}

void	heartbeats_destroy(
	t_heartbeat_entry	*heartbeats_array,
	const t_settings *settings)
{
	int	i;

	i = settings->worker_count;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&(heartbeats_array[i].lock));
	}
	free(heartbeats_array);
}

static inline void	on_death(
	int id,
	long time,
	t_shared_ressource *shared_ressource)
{
	shared_ressource->is_terminated = 1;
	pthread_mutex_lock(&shared_ressource->display_lock);
	printf("%ld %i died\n", time, id + 1);
	pthread_mutex_unlock(&shared_ressource->display_lock);
}

int	check_hearbeats(
	t_heartbeat_entry *heartbeats_array,
	const t_settings *settings,
	t_shared_ressource *shared_ressource)
{
	int				i;
	long			tmp_time;
	long			now;
	int				end;

	end = 1;
	i = -1;
	if (get_time_from_start_ms(&now, 0))
		return (1);
	while (++i < settings->worker_count)
	{
		end = 1;
		pthread_mutex_lock(&(heartbeats_array[i].lock));
		tmp_time = heartbeats_array[i].time;
		pthread_mutex_unlock(&(heartbeats_array[i].lock));
		end = (end && (tmp_time == -1));
		if (tmp_time + settings->life_max_time < now && tmp_time >= 0)
		{
			on_death(i, now, shared_ressource);
			return (2);
		}
	}
	return (end);
}

int	monitor_heatbeats(
	t_heartbeat_entry *heartbeats_array,
	const t_settings *settings,
	t_shared_ressource *shared_ressource
	)
{
	int	status;

	while (1)
	{
		status = check_hearbeats(heartbeats_array, settings, shared_ressource);
		if (status)
		{
			return (status);
		}
		usleep(MONITORING_LOOP_INTERVAL);
	}
	return (0);
}
