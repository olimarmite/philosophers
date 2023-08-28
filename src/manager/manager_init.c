/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:57:17 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:11:32 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "worker.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include <stdlib.h>

int	manager_init(t_manager *manager, const t_settings *settings)
{
	if (heartbeats_init(&manager->heartbeats_array, settings))
		return (1);
	if (manager_allocate_workers(manager, settings))
	{
		manager_destroy(manager, settings);
		return (1);
	}
	manager_init_workers_states(manager, settings);
	return (0);
}

pthread_mutex_t	*create_forks(const t_settings *settings)
{
	int				i;
	pthread_mutex_t	*fork_list;

	fork_list = malloc(settings->worker_count * sizeof(pthread_mutex_t));
	i = 0;
	while (i < settings->worker_count)
	{
		if (pthread_mutex_init(&fork_list[i], NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&fork_list[i]);
			}
			return (0);
		}
		++i;
	}
	return (fork_list);
}

int	manager_allocate_workers(t_manager *manager, const t_settings *settings)
{
	manager->states = calloc(settings->worker_count, sizeof(t_worker_state));
	if (manager->states == NULL)
		return (1);
	manager->threads = calloc(settings->worker_count, sizeof(pthread_t));
	if (manager->threads == NULL)
		return (free(manager->states), 1);
	manager->fork_list = create_forks(settings);
	if (manager->fork_list == NULL)
	{
		free(manager->states);
		free(manager->threads);
		return (1);
	}
	manager->shared_ressource = init_shared_ressources();
	if (manager->shared_ressource == NULL)
	{
		free(manager->states);
		free(manager->threads);
		destroy_forks(manager->fork_list, settings);
		return (1);
	}
	return (0);
}

void	manager_init_workers_states(
	t_manager *manager,
	const t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->worker_count)
	{
		manager->states[i].id = i;
		manager->states[i].settings = settings;
		manager->states[i].heartbeats_ptr = &manager->heartbeats_array[i];
		manager->states[i].fork_order = (i % 2);
		manager->states[i].left_fork = &manager->fork_list[i % NB_PHILO];
		manager->states[i].right_fork = &manager->fork_list[(i + 1) % NB_PHILO];
		manager->states[i].should_lock_on_init = (i % 2);
		manager->states[i].phi_state = THINKING;
		manager->states[i].shared_ressource = manager->shared_ressource;
		++i;
	}
}
