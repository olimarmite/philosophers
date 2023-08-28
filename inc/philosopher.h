/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:01:16 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 19:03:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef enum e_fork_order
{
	RIGHT_FORK_FIRST,
	LEFT_FORK_FIRST
}	t_fork_order;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
}	t_philo_state;

static char *const	g_philo_state_name[] = {
[EATING] = "eating",
[SLEEPING] = "sleeping",
[THINKING] = "thinking",
};

#endif
