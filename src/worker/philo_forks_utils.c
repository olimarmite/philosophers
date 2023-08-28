/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:00:33 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 20:11:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

static void	display_fork_taken(t_worker_state *worker_state)
{
	long			now;

	if (get_time_from_start_ms(&now))
	{
		log_err("philo_core", "Cannot get time",
			&worker_state->shared_ressource->display_lock);
	}
	if (worker_state->shared_ressource->is_terminated == 0)
	{
		pthread_mutex_lock(&worker_state->shared_ressource->display_lock);
		printf("%ld %i has taken a fork\n",
			now,
			worker_state->id);
		pthread_mutex_unlock(&worker_state->shared_ressource->display_lock);
	}
}

void	take_forks(t_fork_order order, t_worker_state *worker_state)
{
	if (order == RIGHT_FORK_FIRST)
	{
		pthread_mutex_lock(worker_state->right_fork);
		display_fork_taken(worker_state);
		pthread_mutex_lock(worker_state->left_fork);
		display_fork_taken(worker_state);
	}
	else
	{
		pthread_mutex_lock(worker_state->left_fork);
		display_fork_taken(worker_state);
		pthread_mutex_lock(worker_state->right_fork);
		display_fork_taken(worker_state);
	}
}

void	release_forks(t_fork_order order, t_worker_state *worker_state)
{
	if (order == RIGHT_FORK_FIRST)
	{
		pthread_mutex_unlock(worker_state->right_fork);
		pthread_mutex_unlock(worker_state->left_fork);
	}
	else
	{
		pthread_mutex_unlock(worker_state->left_fork);
		pthread_mutex_unlock(worker_state->right_fork);
	}
}
