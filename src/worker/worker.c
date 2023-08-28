/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:39:03 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 00:11:17 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"
#include "utils.h"
#include "logs.h"

void	*worker_start(void *worker_state)
{
	philo_core((t_worker_state *) worker_state);
	pthread_exit(NULL);
}
