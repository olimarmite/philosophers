/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:52 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/23 14:19:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define NB_PHILO					10
# define EAT_DURATION				500
# define SLEEP_DURATION				100
# define LIFE_MAX_DURATION			1001
# define DEFAULT_PHILO_STATE		EATING

# define MONITORING_LOOP_INTERVAL	10000 //us

# include "philosopher.h"

typedef struct s_settings
{
	int				worker_count;
	t_philo_state	default_state;
	int				eat_duration;
	int				sleep_duration;
	int				life_max_time;
}	t_settings;

int	settings_init(t_settings *settings);

#endif
