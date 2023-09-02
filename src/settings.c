/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:48:22 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 23:18:22 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"
#include "utils.h"

static int	is_settings_valid(t_settings *settings)
{
	int	is_valid;

	is_valid = 1;
	is_valid &= (settings->life_max_time >= 0);
	is_valid &= (settings->max_eat_count >= -1);
	is_valid &= (settings->eat_duration >= 0);
	is_valid &= (settings->sleep_duration >= 0);
	is_valid &= (settings->worker_count > 0);
	return (is_valid);
}

int	settings_init_parse(t_settings *settings, int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc != 5 && argc != 6)
		return (1);
	settings->default_state = DEFAULT_PHILO_STATE;
	settings->max_eat_count = -1;
	error |= ft_atoi(argv[1], &settings->worker_count);
	error |= ft_atoi(argv[2], &settings->life_max_time);
	error |= ft_atoi(argv[3], &settings->eat_duration);
	error |= ft_atoi(argv[4], &settings->sleep_duration);
	if (argc == 6)
		error |= ft_atoi(argv[5], &settings->max_eat_count);
	settings->eat_duration *= 1000;
	settings->sleep_duration *= 1000;
	if (settings->worker_count % 2 == 0)
		settings->think_duration = settings->eat_duration * 1
			- settings->sleep_duration;
	else
		settings->think_duration = settings->eat_duration * 2
			- settings->sleep_duration;
	if (settings->think_duration < 0)
		settings->think_duration = 0;
	return (error | !is_settings_valid(settings));
}
