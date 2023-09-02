/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_heartbeat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 00:09:24 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/01 00:09:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker.h"

void	set_philo_heartbeat(t_heartbeat_entry *heartbeats_ptr, long value)
{
	pthread_mutex_lock(&((*heartbeats_ptr).lock));
	(*heartbeats_ptr).time = value;
	pthread_mutex_unlock(&((*heartbeats_ptr).lock));
}
