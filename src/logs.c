/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:07:16 by olimarti          #+#    #+#             */
/*   Updated: 2023/08/12 15:34:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	log_err(char *name, char *err)
{
	printf("ERROR: %s: %s\n", name, err);
}

void	log_warn(char *name, char *err)
{
	printf("WARN: %s: %s\n", name, err);

}

void	log_info(char *name, char *err)
{
	printf("INFO: %s: %s\n", name, err);
}
