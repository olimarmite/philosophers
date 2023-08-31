/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:07:16 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 23:20:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

void	log_err(char *name, char *err, pthread_mutex_t *lock)
{
	if (lock == NULL)
	{
		printf("ERROR: %s: %s\n", name, err);
		return ;
	}
	pthread_mutex_lock(lock);
	printf("ERROR: %s: %s\n", name, err);
	pthread_mutex_unlock(lock);
}

void	log_warn(char *name, char *err, pthread_mutex_t *lock)
{
	if (lock == NULL)
	{
		printf("WARN: %s: %s\n", name, err);
		return ;
	}
	pthread_mutex_lock(lock);
	printf("WARN: %s: %s\n", name, err);
	pthread_mutex_unlock(lock);
}

void	log_info(char *name, char *err, pthread_mutex_t *lock)
{
	if (lock == NULL)
	{
		printf("INFO: %s: %s\n", name, err);
		return ;
	}
	pthread_mutex_lock(lock);
	printf("INFO: %s: %s\n", name, err);
	pthread_mutex_unlock(lock);
}
