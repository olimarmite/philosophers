/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:00:56 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:54:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"

static inline void	philo_go_eat(t_worker_state *worker_state)
{
	take_forks(worker_state->fork_order, worker_state);
	philo_eat(worker_state);
	release_forks(worker_state->fork_order, worker_state);
}

static inline void	philo_pre_start(t_worker_state *worker_state)
{
	if (worker_state->should_lock_on_init)
	{
		take_forks(worker_state->fork_order, worker_state);
	}
	philo_set_ready(worker_state);
}

static inline void	philo_post_start(t_worker_state *worker_state)
{
	if (worker_state->should_lock_on_init)
	{
		if (worker_state->shared_ressource->is_terminated == 0)
			philo_eat(worker_state);
		release_forks(worker_state->fork_order, worker_state);
	}
	else
	{
		if (worker_state->shared_ressource->is_terminated == 0)
			philo_go_eat(worker_state);
	}
}

void	philo_core(t_worker_state *worker_state)
{
	int	eated_times;
	int	max_eat_count;

	eated_times = 1;
	max_eat_count = worker_state->settings->max_eat_count;
	philo_pre_start(worker_state);
	philo_wait_starting(worker_state);
	philo_post_start(worker_state);
	while ((max_eat_count == -1 || eated_times < max_eat_count)
		&& worker_state->shared_ressource->is_terminated == 0)
	{
		philo_sleep(worker_state);
		philo_think(worker_state);
		philo_go_eat(worker_state);
		++eated_times;
	}
	*worker_state->heartbeats_ptr = -1;
}
