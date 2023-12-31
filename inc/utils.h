/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:52 by olimarti          #+#    #+#             */
/*   Updated: 2023/09/01 00:24:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <pthread.h>

int		get_time_ms(long *const time);
int		get_time_from_start_ms(long *const time, int can_init);
void	increment_mutex_int(int *variable, pthread_mutex_t *mutex);
int		read_mutex_int(int *variable, pthread_mutex_t *mutex);

int		ft_atoi(const char *nptr, int *nbr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
