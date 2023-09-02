/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:28:04 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/01 00:14:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"
#include "worker.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"
#include <stdlib.h>

int	destroy_forks(pthread_mutex_t *fork_list, const t_settings *settings)
{
	int					i;
	int					error;

	i = 0;
	error = 0;
	while (i < settings->worker_count)
	{
		error |= pthread_mutex_destroy(&fork_list[i]);
		++i;
	}
	free(fork_list);
	return (0);
}

void	manager_destroy_workers(t_manager *manager, const t_settings *settings)
{
	free(manager->states);
	free(manager->threads);
	destroy_forks(manager->fork_list, settings);
	destroy_shared_ressources(manager->shared_ressource);
}

void	manager_destroy(t_manager *manager, const t_settings *settings)
{
	heartbeats_destroy(manager->heartbeats_array, settings);
	manager_destroy_workers(manager, settings);
}
