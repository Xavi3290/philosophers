/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:54 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/25 12:04:57 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	*init_list(int philo_num)
{
	int	*list;
	int	i;
	int	id;

	id = 1;
	i = 0;
	list = malloc(sizeof(int) * philo_num);
	if (!list)
		return (NULL);
	while (id <= philo_num)
	{
		list[i] = id;
		i++;
		id += 2;
	}
	id = 2;
	while (id <= philo_num)
	{
		list[i] = id;
		i++;
		id += 2;
	}
	return (list);
}

static pthread_mutex_t	*init_forks(int philo_num)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!fork)
		return (NULL);
	while (i < philo_num)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (NULL);
		i++;
	}
	return (fork);
}

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
	data->fork = init_forks(data->philo_num);
	if (!data->fork)
		return (NULL);
	data->list = init_list(data->philo_num);
	if (!data->list)
		return (NULL);
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	else
		data->num_to_eat = 0;
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
