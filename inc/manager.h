/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:30:24 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/12 17:01:59 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MANAGER_H
# define MANAGER_H

# include <stdatomic.h>
# include "settings.h"

typedef struct s_manager
{
	atomic_long	*heartbeats_array;
}	t_manager;

int		manager_init(t_manager *manager, const t_settings *settings);
int		manager_start(t_manager *manager, const t_settings *settings);
void	manager_destroy(t_manager *manager);

int		heartbeats_init(
			atomic_long	**heartbeats_array,
			const t_settings *settings
			);

int		monitor_heatbeats(
			const atomic_long	*heartbeats_array,
			const t_settings	*settings
			);

int		monitor_heatbeats(
			const atomic_long	*heartbeats_array,
			const t_settings *settings
			);

#endif
