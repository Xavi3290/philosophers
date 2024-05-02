/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:17 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/02 18:01:23 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleap = ft_atoi(argv[4]);
	data->alive = 1;
	data->start = get_time_ms();
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	else
		data->num_to_eat = 0;
	if (sem_unlink("p_fork") == -1 || sem_unlink("p_print") == -1)
		return (NULL);
	data->print = sem_open("/p_print", O_CREAT, 0700, 1);
	data->fork = sem_open("/p_fork", O_CREAT, 0700, data->philo_num);
	if (data->print == -1 || data->fork == -1)
		return (NULL);
	return (data);
}

t_philo	*init_philos(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	i = 0;
	data = init_data(argc, argv);
	if (!data)
		return (NULL);
	philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!philo)
		return (NULL);
	while (i < data->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].time_last_meal = 0;
		philo[i].num_eat = 0;
		i++;
	}
	return (philo);
}
