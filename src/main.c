/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:53 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/31 22:37:17 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdatomic.h>
#include "logs.h"
#include "utils.h"
#include "settings.h"
#include "manager.h"

int	main(int argc, char *argv[])
{
	t_manager	manager;
	t_settings	settings;

	if (settings_init_parse(&settings, argc, argv))
		return (1);
	if (manager_init(&manager, &settings))
		return (1);
	manager_start(&manager, &settings);
	manager_destroy(&manager, &settings);
}
