/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:25 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/03 18:14:19 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	free_sem_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	if (sem_close(philo->data->fork) == -1 || sem_close(philo->data->print) == \
		-1)
		return (1);
	if (sem_unlink("/p_fork") == -1 || sem_unlink("/p_print") == -1)
		return (1);
	free(philo->data);
	free(philo);
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
				return (printf("Write numbers\n"));
			j++;
		}
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("Write numbers\n"));
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
	int		i;

	i = 0;
	if (error_syntax(argv) || check_args(argc, argv))
		exit(EXIT_FAILURE);
	philo = init_philos(argc, argv);
	if (!philo)
		exit(EXIT_FAILURE);
	while (i < philo->data->philo_num)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			exit(EXIT_FAILURE);
		if (philo[i].pid == 0)
			actions(&(philo[i]));
		i++;
	}
	if (free_sem_data(philo))
		exit(EXIT_FAILURE);
	return (0);
}
