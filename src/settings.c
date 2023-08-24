/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:48:22 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/23 13:42:21 by olimarti         ###   ########.fr       */
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
	return (0);
}
