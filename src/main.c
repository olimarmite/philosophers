/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:23:53 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/12 16:58:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdatomic.h>
#include "logs.h"
#include "utils.h"
#include "settings.h"
#include "manager.h"

int	main(void)
{
	t_manager	manager;
	t_settings	settings;

	settings_init(&settings);
	if (manager_init(&manager, &settings))
		return (1);
	manager_start(&manager, &settings);
	manager_destroy(&manager);
}
