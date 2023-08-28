/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:48:22 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/28 03:23:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

int	settings_init(t_settings *settings)
{
	settings->default_state = DEFAULT_PHILO_STATE;
	settings->life_max_time = LIFE_MAX_DURATION;
	settings->eat_duration = EAT_DURATION * 1000;
	settings->sleep_duration = SLEEP_DURATION * 1000;
	settings->worker_count = NB_PHILO;
	settings->max_eat_count = MAX_EAT_COUNT;
	if (settings->worker_count % 2 == 0)
		settings->think_duration = settings->eat_duration * 1
			- settings->sleep_duration;
	else
		settings->think_duration = settings->eat_duration * 2
			- settings->sleep_duration;
	if (settings->think_duration < 0)
		settings->think_duration = 0;
	return (0);
}
