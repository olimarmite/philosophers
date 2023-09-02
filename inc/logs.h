/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:11:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 23:28:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

# include <stdio.h>
# include <pthread.h>

# define LOG_LEVEL_ERROR	1
# define LOG_LEVEL_WARN		2
# define LOG_LEVEL_INFO		3

# ifndef LOG_LEVEL
#  define LOG_LEVEL			LOG_LEVEL_ERROR
# endif

void	log_err(char *name, char *err, pthread_mutex_t *lock);
void	log_warn(char *name, char *err, pthread_mutex_t *lock);
void	log_info(char *name, char *err, pthread_mutex_t *lock);

#endif
