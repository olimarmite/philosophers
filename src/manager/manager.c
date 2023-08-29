/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:28:04 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/29 19:54:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "worker.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include <stdlib.h>

// static int	manager_start_half_workers(
// 	int start, t_manager *manager,
// 	const t_settings *settings)
// {
// 	int	spawned;

// 	spawned = 0;
// 	while (start < settings->worker_count)
// 	{
// 		if (pthread_create(&manager->threads[start],
// 				NULL,
// 				&worker_start,
// 				(void *)&manager->states[start]))
// 		{
// 			return (spawned);
// 		}
// 		start += 2;
// 		++spawned;
// 	}
// 	return (spawned);
// }

static int	manager_start_half_workers(
	int first_wave,
	t_manager *manager,
	const t_settings *settings)
{
	int	spawned;
	int	i;

	spawned = 0;
	i = 0;
	while (i < settings->worker_count)
	{
		if ((manager->states[i].should_lock_on_init != 0) == (first_wave == 0))
		{
			if (pthread_create(&manager->threads[i],
					NULL,
					&worker_start,
					(void *)&manager->states[i]))
			{
				return (spawned);
			}
			++spawned;
		}
		++i;
	}
	return (spawned);
}

static int	manager_start_threads(
	t_manager *manager,
	const t_settings *settings)
{
	int	spawned;

	spawned = manager_start_half_workers(1, manager, settings);
	while (read_mutex_int(&manager->shared_ressource->worker_ready_count,
			&manager->shared_ressource->worker_ready_count_lock) < spawned)
	{
		usleep(100000);
	}
	spawned += manager_start_half_workers(0, manager, settings);
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
		if (monitor_heatbeats(manager->heartbeats_array, settings,
			&manager->shared_ressource->display_lock) == 2)
			manager->shared_ressource->is_terminated = 1;
	}
	else
	{
		pthread_mutex_unlock(&manager->shared_ressource->start_lock);
		manager->shared_ressource->is_terminated = 1;
	}
	manager_join_threads(manager, settings);
	return (0);
}
