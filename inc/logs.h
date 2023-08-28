/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:11:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 19:09:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

void	log_err(char *name, char *err, pthread_mutex_t *lock);
void	log_warn(char *name, char *err, pthread_mutex_t *lock);
void	log_info(char *name, char *err, pthread_mutex_t *lock);

#endif
