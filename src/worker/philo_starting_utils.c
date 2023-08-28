/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_starting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 03:55:26 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:55:41 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

void	philo_wait_starting(t_worker_state *worker_state)
{
	pthread_mutex_lock(&worker_state->shared_ressource->start_lock);
	pthread_mutex_unlock(&worker_state->shared_ressource->start_lock);
}

void	philo_set_ready(t_worker_state *worker_state)
{
	increment_mutex_int(
		&worker_state->shared_ressource->worker_ready_count,
		&worker_state->shared_ressource->worker_ready_count_lock
		);
}
