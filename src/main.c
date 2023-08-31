/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:53 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 23:12:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdatomic.h>
#include "logs.h"
#include "utils.h"
#include "settings.h"
#include "manager.h"

void	display_invalid_usage(char *prog_name)
{
	log_err(prog_name, "Invalid usage\n\n\n"
		"Arguments expected:\n\n"
		"\tnumber_of_philosophers\n"
		"\ttime_to_die (in milliseconds)\n"
		"\ttime_to_eat (in milliseconds)\n"
		"\ttime_to_sleep (in milliseconds)\n"
		"\tnumber_of_times_each_philosopher_must_eat (optional argument)\n",
		NULL);
}

int	main(int argc, char *argv[])
{
	t_manager	manager;
	t_settings	settings;

	if (settings_init_parse(&settings, argc, argv))
	{
		display_invalid_usage(argv[0]);
		return (1);
	}
	if (manager_init(&manager, &settings))
		return (1);
	manager_start(&manager, &settings);
	manager_destroy(&manager, &settings);
}
