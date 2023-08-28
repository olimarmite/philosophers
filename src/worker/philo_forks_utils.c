/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:00:33 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 00:00:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"

void	take_forks(t_fork_order order, t_worker_state *worker_state)
{
	if (order == RIGHT_FORK_FIRST)
	{
		pthread_mutex_lock(worker_state->right_fork);
		pthread_mutex_lock(worker_state->left_fork);
	}
	else
	{
		pthread_mutex_lock(worker_state->left_fork);
		pthread_mutex_lock(worker_state->right_fork);
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
