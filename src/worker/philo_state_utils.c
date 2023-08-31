/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:53:48 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 22:41:35 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

static void	display_state(t_worker_state *worker_state)
{
	long			now;

	if (get_time_from_start_ms(&now, 0))
	{
		log_err("display_state", "Cannot get time",
			&worker_state->shared_ressource->display_lock);
	}
	pthread_mutex_lock(&worker_state->shared_ressource->display_lock);
	if (worker_state->shared_ressource->is_terminated == 0)
	{
		printf("%ld %i is %s\n",
			now,
			worker_state->id + 1,
			g_philo_state_name[worker_state->phi_state]);
	}
	pthread_mutex_unlock(&worker_state->shared_ressource->display_lock);
}

static inline int	philo_change_state(
		t_philo_state state,
		int duration,
		t_worker_state *worker_state)
{
	worker_state->phi_state = state;
	display_state(worker_state);
	usleep(duration);
	return (0);
}

void	philo_eat(t_worker_state *worker_state)
{
	long			now;

	if (get_time_from_start_ms(&now, 0))
	{
		log_err("philo_eat", "Cannot get time",
			&worker_state->shared_ressource->display_lock);
	}
	*worker_state->heartbeats_ptr = now;
	philo_change_state(EATING,
		worker_state->settings->eat_duration, worker_state);
}

void	philo_sleep(t_worker_state *worker_state)
{
	philo_change_state(SLEEPING,
		worker_state->settings->sleep_duration, worker_state);
}

void	philo_think(t_worker_state *worker_state)
{
	philo_change_state(THINKING,
		worker_state->settings->think_duration, worker_state);
}
