/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:41 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/07 13:26:56 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	modify_list(t_data *data, int id)
{
	int	i;

	i = 0;
	while (i < data->philo_num - 1)
	{
		data->list[i] = data->list[i + 1];
		i++;
	}
	data->list[i] = id;
}
