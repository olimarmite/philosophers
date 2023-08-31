/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:37:52 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 22:42:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define DEFAULT_PHILO_STATE		EATING
# define MONITORING_LOOP_INTERVAL	1000

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

#endif
