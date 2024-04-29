/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:41 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/29 20:49:36 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleeping(t_philo *philo, long long time_eat)
{
	long long	time_ms;

	time_ms = get_time_ms();
	check_alive(philo);
	while (philo->data->alive)
	{
		if (get_time_ms() - time_ms > philo->data->time_die - 1)
			print_dead(philo);
		if (get_time_ms() >= time_eat)
			break ;
		usleep(50);
	}
}

static void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->fork[philo->id - 1]))
		return ;
	print_info(philo, "has taken a fork");
	if (philo->id == philo->data->philo_num)
    {
		if (pthread_mutex_lock(&philo->data->fork[0]))
			return ;
    }
	else
    {
        if (pthread_mutex_lock(&philo->data->fork[philo->id]))
			return ;
    }
	print_info(philo, "has taken a fork");
	modify_list(philo->data, philo->id);
	print_info(philo, "is eating");
	philo->time_last_meal = get_time_ms();
	philo->num_eat++;
	sleeping(philo, philo->data->time_eat);
	eating_unlock(philo);
}

static void	routine(t_philo *philo)
{
	while (philo->data->alive)
	{
		check_alive(philo);
		if (philo->id != philo->data->list[0])
			continue ;
		if (philo->data->philo_num != 1)
		{
			eating(philo);
			if (philo->data->num_to_eat
				&& philo->num_eat == philo->data->num_to_eat)
				break ;
			print_info(philo, "is sleeping");
			sleeping(philo, philo->data->time_sleap);
			print_info(philo, "is thinking");
		}
		check_alive(philo);
	}
}

static void	*is_alive(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (philo->data->alive)
		check_alive(philo);
	return (NULL);
}

void	*actions(void *void_philo)
{
	t_philo		*philo;
	pthread_t	thr;

	philo = void_philo;
	if (pthread_create(&thr, NULL, is_alive, philo))
		return (NULL);
	if (pthread_detach(thr))
		return (NULL);
	routine(philo);
	return (0);
}
