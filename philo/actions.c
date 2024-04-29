/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:41 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/29 17:17:55 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
}

int	check_alive(t_philo *philo)
{
	long long	time_ms;

	time_ms = get_time_ms();
	if (philo->time_last_meal == 0)
		philo->time_last_meal = get_time_ms() - 1;
	if (philo->data->alive == 0)
		return (0);
	if (time_ms - philo->time_last_meal > philo->data->time_die)
	{
		print_dead(philo);
		return (0);
	}
	return (1);
}

void	*is_alive(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (philo->data->alive)
		check_alive(philo);
}

void	*actions(void *void_philo)
{
	t_philo		*philo;
	pthread_t	thr;

	philo = void_philo;
	if (pthread_create(&thr, NULL, is_alive, philo))
		return (1);
	if (pthread_detach(thr))
		return (1);
	while (philo->data->alive)
	{
		check_alive(philo);
		if (philo->id != philo->data->list[0])
			continue ;
		check_alive(philo);
	}
	return (0);
}
