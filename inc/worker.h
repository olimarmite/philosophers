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

typedef struct s_worker_state
{
	int					id;
	const t_settings	*settings;
	atomic_long			*heartbeats_ptr;
	t_fork_order		fork_order;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_philo_state		phi_state;
}	t_worker_state;

void	*worker_start(void *worker_state);

#endif
