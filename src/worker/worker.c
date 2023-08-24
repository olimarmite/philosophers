/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:39:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/24 16:42:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

// void worker_init()
// {
// 	t_worker_state worker_state;

// }


void	eat(t_worker_state *worker_state)
{
	long 			now;

	if (get_time_ms(&now))
	{
		log_err("philo_core", "Cannot get time");
	}
	*worker_state->heartbeats_ptr = now;
	worker_state->phi_state = EATING;
	// printf("[%ld] [%i] is %s\n",
	// 		now, worker_state->id, g_philo_state_name[worker_state->phi_state]);
	usleep(worker_state->settings->eat_duration);
}

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

void	go_eat(t_worker_state *worker_state)
{
	take_forks(worker_state->fork_order, worker_state);
	eat(worker_state);
	release_forks(worker_state->fork_order, worker_state);
}

void	philo_core(t_worker_state worker_state)
{
	long 			now;

	while (1)
	{


		if (get_time_ms(&now))
		{
			log_err("philo_core", "Cannot get time");
		}
		go_eat(&worker_state);
		worker_state.phi_state = SLEEPING;

		// printf("[%i]: %ld\n", worker_state.id , now);
		// printf("[%ld] [%i] is %s\n",
		// 	now,
		// 	worker_state.id, g_philo_state_name[worker_state.phi_state]);
		//usleep(100000);
		usleep(worker_state.settings->sleep_duration);
		worker_state.phi_state = THINKING;
		// printf("[%ld] [%i] is %s\n",
		// 	now,
		// 	worker_state.id, g_philo_state_name[worker_state.phi_state]);
		// ++i;
	}
	printf("%i: Quit\n",  worker_state.id);
}

void	*worker_start(void *worker_state)
{
	philo_core(*(t_worker_state*)worker_state);
	pthread_exit(NULL);
}
