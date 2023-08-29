/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:52 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/29 16:50:14 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

// # define NB_PHILO					4
// # define EAT_DURATION				100
// # define SLEEP_DURATION				10
// # define LIFE_MAX_DURATION			210
// # define MAX_EAT_COUNT				-1
# define DEFAULT_PHILO_STATE		EATING

# define MONITORING_LOOP_INTERVAL	1000 //us

# include "philosopher.h"

typedef struct s_settings
{
	int				worker_count;
	t_philo_state	default_state;
	int				eat_duration;
	int				sleep_duration;
	int				think_duration;
	int				life_max_time;
	int				max_eat_count;
}	t_settings;

int	settings_init_parse(t_settings *settings, int argc, char **argv);
// int	settings_init_default(t_settings *settings);


#endif
