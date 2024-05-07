/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:04:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/07 16:51:32 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_threads_and_philo(t_philo *philo, pthread_t *thr)
{
	int	i;

	i = 0;
	free(thr);
	while (i < philo->data->philo_num)
		if (pthread_mutex_destroy(&philo->data->fork[i++]))
			return (1);
	free(philo->data->fork);
	free(philo->data->list);
	if (pthread_mutex_destroy(&philo->data->print))
		return (1);
	free(philo->data);
	free(philo);
	return (0);
}

static int	threads(t_philo *philo)
{
	int			i;
	pthread_t	*thr;

	i = 0;
	thr = malloc(sizeof(pthread_t) * (philo->data->philo_num));
	if (!thr)
		return (1);
	while (i < philo->data->philo_num)
	{
		if (pthread_create(&thr[i], NULL, actions, &philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < philo->data->philo_num)
	{
		if (pthread_join(thr[i], NULL))
			return (1);
		i++;
	}
	if (free_threads_and_philo(philo, thr))
		return (1);
	return (0);
}

static int	error_syntax(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (!argv[i][j])
			return (1);
		if (argv[i][j] == '-' || argv[i][j] == '+')
		{
			if (!(argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				return (printf("Must be numbers.\n"));
			j++;
		}
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("Must be numbers.\n"));
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) < 1)
			return (printf("There must be at least 1 philosopher.\n"));
		if (ft_atoi(argv[2]) < 1)
			return (printf("Time_to_die must be at least 1.\n"));
		if (ft_atoi(argv[3]) < 1)
			return (printf("Time_to_eat must be at least 1.\n"));
		if (ft_atoi(argv[4]) < 1)
			return (printf("Time_to_sleep must be at least 1.\n"));
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Number_of_times_each_philosopher_must_eat \
            ust be at least 1.\n"));
	}
	else
		return (printf("[number_of_philosophers] [time_to_die] \
        [time_to_eat] [time_to_sleep]\nOptional \
        [number_of_times_each_philosopher_must_eat]\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (error_syntax(argv) || check_args(argc, argv))
		return (1);
	philo = init_philos(argc, argv);
	if (!philo)
		return (1);
	if (threads(philo))
		return (1);
	return (0);
}
