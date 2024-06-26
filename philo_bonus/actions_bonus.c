/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:13 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/07 13:27:28 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	sleeping(t_philo *philo, long long time_eat_sleep)
{
	long long	time_ms;

	time_ms = get_time_ms();
	philo->data->alive = check_alive(philo);
	while (philo->data->alive)
	{
		if (get_time_ms() - time_ms > philo->data->time_die - 1)
		{
			if (print_dead(philo))
				return (1);
		}
		if (get_time_ms() - time_ms >= time_eat_sleep)
			break ;
		usleep(50);
	}
	return (0);
}

static int	eating(t_philo *philo)
{
	if (sem_wait(philo->data->fork) == -1 || print_info(philo,
			"has taken a fork"))
		return (1);
	if (sem_wait(philo->data->fork) == -1 || print_info(philo,
			"has taken a fork"))
		return (1);
	if (print_info(philo, "is eating"))
		return (1);
	philo->time_last_meal = get_time_ms();
	philo->num_eat++;
	if (sem_post(philo->data->sem_eat))
		return (1);
	if (sleeping(philo, philo->data->time_eat))
		return (1);
	if (sem_post(philo->data->fork) == -1 || sem_post(philo->data->fork) == -1)
		return (1);
	return (0);
}

static int	routine(t_philo *philo)
{
	while (philo->data->alive)
	{
		if (philo->data->philo_num != 1)
		{
			if (eating(philo))
				return (1);
			if (philo->data->num_to_eat
				&& philo->num_eat == philo->data->num_to_eat)
				break ;
			if (print_info(philo, "is sleeping") || sleeping(philo,
					philo->data->time_sleap) || print_info(philo,
					"is thinking"))
				return (1);
		}
		philo->data->alive = check_alive(philo);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

static void	*actions(void *void_philo)
{
	t_philo		*philo;
	pthread_t	thr;

	philo = (t_philo *)void_philo;
	if (pthread_create(&thr, NULL, &is_alive, philo) || pthread_detach(thr))
		return (NULL);
	if (philo->data->philo_num == 1)
	{
		if (print_info(philo, "has taken a fork"))
			return (NULL);
	}
	if (routine(philo))
		return (NULL);
	return (0);
}

int	do_actions(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			exit(EXIT_FAILURE);
		if (philo[i].pid == 0)
			actions(&(philo[i]));
		i++;
	}
	if (sem_wait(philo->data->sem_alive))
		return (1);
	philo->data->alive = 0;
	if (sem_post(philo->data->sem_eat))
		return (1);
	return (0);
}
