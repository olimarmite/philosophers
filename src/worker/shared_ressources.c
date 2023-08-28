/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_ressources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:34:02 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:30:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"

static int	init_shared_ress2(t_shared_ressource	*shared_ressource)
{
	shared_ressource->is_terminated = ATOMIC_VAR_INIT(0);
	return (0);
}

t_shared_ressource	*init_shared_ressources(void)
{
	t_shared_ressource	*shared_ressource;
	int					initialized_flag;

	initialized_flag = 0;
	shared_ressource = malloc(sizeof(t_shared_ressource));
	if (shared_ressource == NULL)
		return (NULL);
	shared_ressource->worker_ready_count = 0;
	if (pthread_mutex_init(&shared_ressource->display_lock, NULL) == 0)
		initialized_flag |= 0b000000001;
	if (pthread_mutex_init(&shared_ressource->start_lock, NULL) == 0)
		initialized_flag |= 0b000000010;
	if (pthread_mutex_init(&shared_ressource->worker_ready_count_lock, NULL)
		== 0)
		initialized_flag |= 0b000000100;
	if (initialized_flag == 0b000000111 && !init_shared_ress2(shared_ressource))
		return (shared_ressource);
	if (initialized_flag & 0b000000001)
		pthread_mutex_destroy(&shared_ressource->display_lock);
	if (initialized_flag & 0b000000010)
		pthread_mutex_destroy(&shared_ressource->start_lock);
	if (initialized_flag & 0b000000100)
		pthread_mutex_destroy(&shared_ressource->worker_ready_count_lock);
	free(shared_ressource);
	return (shared_ressource);
}

void	destroy_shared_ressources(t_shared_ressource *shared_ressource)
{
	pthread_mutex_destroy(&shared_ressource->display_lock);
	pthread_mutex_destroy(&shared_ressource->start_lock);
	pthread_mutex_destroy(&shared_ressource->worker_ready_count_lock);
	free(shared_ressource);
}
