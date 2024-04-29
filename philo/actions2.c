/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:41 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/29 20:25:47 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void modify_list(t_data *data, int id)
{
	int i;

	i = 0;
	while (i < data->philo_num - 1)
	{
		data->list[i] = data->list[i + 1];
		i++;
	}
	data->list[i] = id;
}

void eating_unlock(t_philo *philo)
{
    if (pthread_mutex_unlock(&philo->data->fork[philo->id - 1]))
		return ;
	if (philo->id == philo->data->philo_num)
    {
		if (pthread_mutex_unlock(&philo->data->fork[0]))
			return ;
    }
	else
    {
        if (pthread_mutex_unlock(&philo->data->fork[philo->id]))
			return ;
    }
}