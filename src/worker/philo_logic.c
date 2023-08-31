/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:00:56 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 22:41:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

static void	philo_go_eat(t_worker_state *worker_state)
{
	take_forks(worker_state->fork_order, worker_state);
	philo_eat(worker_state);
	release_forks(worker_state->fork_order, worker_state);
}

static inline void	philo_pre_start(t_worker_state *worker_state)
{
	philo_set_ready(worker_state);
}

static inline void	philo_post_start(
	t_worker_state *worker_state)
{
	long	now;

	now = 0;
	if (worker_state->right_fork == worker_state->left_fork)
	{
		take_single_fork(worker_state->left_fork, worker_state);
		while (!worker_state->shared_ressource->is_terminated)
			usleep(MONITORING_LOOP_INTERVAL);
		release_single_fork(worker_state->left_fork);
	}
	if (get_time_from_start_ms(&now, 0))
	{
		log_err("philo_eat", "Cannot get time",
			&worker_state->shared_ressource->display_lock);
	}
	*worker_state->heartbeats_ptr = now;
	if (worker_state->should_lock_on_init)
		worker_state->phi_state = EATING;
	else
	{
		worker_state->phi_state = THINKING;
		if (worker_state->shared_ressource->is_terminated == 0)
			usleep(worker_state->settings->eat_duration);
	}
}

void	philo_core(t_worker_state *worker_state)
{
	int		eated_times;
	int		max_eat_count;

	eated_times = 0;
	max_eat_count = worker_state->settings->max_eat_count;
	philo_pre_start(worker_state);
	philo_wait_starting(worker_state);
	philo_post_start(worker_state);
	while ((max_eat_count == -1 || eated_times < max_eat_count)
		&& worker_state->shared_ressource->is_terminated == 0)
	{
		philo_go_eat(worker_state);
		++eated_times;
		philo_sleep(worker_state);
		philo_think(worker_state);
	}
	*worker_state->heartbeats_ptr = -1;
}
