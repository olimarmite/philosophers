/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_getter_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:06:32 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:31:05 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	read_mutex_int(int *variable, pthread_mutex_t *mutex)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	increment_mutex_int(int *variable, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*variable += 1;
	pthread_mutex_unlock(mutex);
}
