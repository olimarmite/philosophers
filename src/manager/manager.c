/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:28:04 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/23 13:58:34 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "worker.h"
#include "philosopher.h"
#include <stdlib.h>

int	manager_init(t_manager *manager, const t_settings *settings)
{
	if (heartbeats_init(&manager->heartbeats_array, settings))
		return (1);
	return (0);
}

pthread_mutex_t	*create_forks(const t_settings *settings)
{
	int				i;
	pthread_mutex_t	*fork_list;

	fork_list = malloc(settings->worker_count * sizeof(pthread_mutex_t));
	i = 0;
	while (i < NB_PHILO)
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

int	manager_start(t_manager *manager, const t_settings *settings)
{
	t_worker_state		*states;
	pthread_mutex_t		*fork_list;
	int					i;
	pthread_t			thread;

	i = 0;
	states = calloc(settings->worker_count, sizeof(t_worker_state));
	fork_list = create_forks(settings);
	if (fork_list == NULL)
		return (1);
	while (i < settings->worker_count)
	{
		states[i].id = i;
		states[i].settings = settings;
		states[i].heartbeats_ptr = &manager->heartbeats_array[i];
		states[i].fork_order = (i % 2);
		states[i].left_fork = &fork_list[i % NB_PHILO];
		states[i].right_fork = &fork_list[(i + 1) % NB_PHILO];
		states[i].phi_state = THINKING;
		pthread_create(&thread, NULL, &worker_start, (void *)&states[i]);
		++i;
	}

	i = 0;
	while (i < settings->worker_count)
	{
		// printf("%i\n", states[i].id);
		++i;
	}
	return (monitor_heatbeats(manager->heartbeats_array, settings));
}

void	manager_destroy(t_manager *manager)
{
	free(manager->heartbeats_array);
}
