/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:28:04 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/03 00:19:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "worker.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include <stdlib.h>

static int	manager_start_all_workers(
	t_manager *manager,
	const t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->worker_count)
	{
		if (pthread_create(&manager->threads[i],
				NULL,
				&worker_start,
				(void *)&manager->states[i]))
		{
			manager->threads[i] = 0;
			return (i);
		}
		++i;
	}
	return (i);
}

static int	manager_start_threads(
	t_manager *manager,
	const t_settings *settings)
{
	int	spawned;

	spawned = manager_start_all_workers(manager, settings);
	while (read_mutex_int(&manager->shared_ressource->worker_ready_count,
			&manager->shared_ressource->worker_ready_count_lock) < spawned)
	{
		usleep(100000);
	}
	return (spawned);
}

static void	manager_join_threads(t_manager *manager, const t_settings *settings)
{
	int	i;

	log_info("Manager", "wait all threads",
		&manager->shared_ressource->display_lock);
	i = settings->worker_count;
	while (i > 0)
	{
		--i;
		if (manager->threads[i])
			pthread_join(manager->threads[i], NULL);
	}
	log_info("Manager", "all threads terminated",
		&manager->shared_ressource->display_lock);
}

static void	init_start_time(void)
{
	long	time;

	get_time_from_start_ms(&time, 1);
}

int	manager_start(t_manager *manager, const t_settings *settings)
{
	int	spawned_count;

	pthread_mutex_lock(&manager->shared_ressource->start_lock);
	spawned_count = manager_start_threads(manager, settings);
	init_start_time();
	if (spawned_count == settings->worker_count)
	{
		pthread_mutex_unlock(&manager->shared_ressource->start_lock);
		monitor_heatbeats(manager->heartbeats_array, settings,
			manager->shared_ressource);
	}
	else
	{
		pthread_mutex_unlock(&manager->shared_ressource->start_lock);
		manager->shared_ressource->is_terminated = 1;
	}
	manager_join_threads(manager, settings);
	return (0);
}
