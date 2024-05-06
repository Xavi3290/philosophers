/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:17 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/06 19:37:11 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_data	*open_sem(t_data *data)
{
	sem_unlink("/p_fork");
	sem_unlink("/p_print");
	sem_unlink("/p_alive");
	sem_unlink("/p_eat");
	data->sem_eat = sem_open("/p_eat", O_CREAT, 0700, 0);
	data->sem_alive = sem_open("/p_alive", O_CREAT, 0700, 0);
	data->print = sem_open("/p_print", O_CREAT, 0700, 1);
	data->fork = sem_open("/p_fork", O_CREAT, 0700, data->philo_num);
	if (data->print == SEM_FAILED || data->fork == SEM_FAILED)
		return (NULL);
	if (data->sem_alive == SEM_FAILED || data->sem_eat == SEM_FAILED)
		return (NULL);
	return (data);
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
	if (argc == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	else
		data->num_to_eat = 0;
	data = open_sem(data);
	if (!data)
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

void	*is_alive(void *v_philo)
{
	t_philo	*philo;

	philo = v_philo;
	while (philo->data->alive)
		philo->data->alive = check_alive(philo);
	return (NULL);
}
