/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WORKER.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:30:24 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/12 17:01:59 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_H
# define WORKER_H

# include <stdatomic.h>
# include "settings.h"
# include "philosopher.h"

typedef struct s_shared_ressource
{
	pthread_mutex_t		start_lock;
	int					worker_ready_count;
	pthread_mutex_t		worker_ready_count_lock;
	pthread_mutex_t		display_lock;
	atomic_bool			is_terminated;
}	t_shared_ressource;

typedef struct s_heartbeat_entry
{
	long			time;
	pthread_mutex_t	lock;
}	t_heartbeat_entry;

typedef struct s_worker_state
{
	int					id;
	const t_settings	*settings;
	t_heartbeat_entry	*heartbeats_ptr;
	t_fork_order		fork_order;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_philo_state		phi_state;
	int					should_lock_on_init;
	t_shared_ressource	*shared_ressource;
}	t_worker_state;

void				*worker_start(void *worker_state);
t_shared_ressource	*init_shared_ressources(void);
void				destroy_shared_ressources(
						t_shared_ressource *shared_ressource);

void				philo_eat(t_worker_state *worker_state);
void				philo_sleep(t_worker_state *worker_state);
void				philo_think(t_worker_state *worker_state);

void				take_forks(
						t_fork_order order,
						t_worker_state *worker_state);
void				release_forks(t_fork_order order,
						t_worker_state *worker_state);

void				take_single_fork(
						pthread_mutex_t *fork,
						t_worker_state *worker_state);
void				release_single_fork(pthread_mutex_t *fork);

void				philo_set_ready(t_worker_state *worker_state);
void				philo_wait_starting(t_worker_state *worker_state);

void				philo_core(t_worker_state *worker_state);

void				set_philo_heartbeat(
						t_heartbeat_entry *heartbeats_ptr,
						long value);

#endif
