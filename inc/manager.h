/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:30:24 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:54:22 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <stdatomic.h>
# include "settings.h"
# include "worker.h"

typedef struct s_manager
{
	atomic_long			*heartbeats_array;
	t_worker_state		*states;
	pthread_mutex_t		*fork_list;
	pthread_t			*threads;
	t_shared_ressource	*shared_ressource;

}	t_manager;

int		manager_init(t_manager *manager, const t_settings *settings);
int		manager_start(t_manager *manager, const t_settings *settings);
void	manager_destroy(t_manager *manager, const t_settings *settings);

int		heartbeats_init(
			atomic_long	**heartbeats_array,
			const t_settings *settings
			);

void	heartbeats_destroy(atomic_long	*heartbeats_array);

int		check_hearbeats(
			const atomic_long *heartbeats_array,
			const t_settings *settings,
			pthread_mutex_t *display_lock
			);

int		manager_allocate_workers(
			t_manager *manager,
			const t_settings *settings
			);

void	manager_init_workers_states(
			t_manager *manager,
			const t_settings *settings
			);

void	manager_destroy_workers(
			t_manager *manager,
			const t_settings *settings
			);

int		destroy_forks(pthread_mutex_t *fork_list,
			const t_settings *settings
			);

int		monitor_heatbeats(
			const atomic_long *heartbeats_array,
			const t_settings *settings,
			pthread_mutex_t *display_lock
			);

#endif
