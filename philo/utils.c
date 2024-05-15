/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:04:19 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/15 16:08:34 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long long	get_time_ms(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_ms);
}

int	print_dead(t_philo *philo)
{
	long long	time_ms;

	if (pthread_mutex_lock(&philo->data->print))
		return (1);
	time_ms = get_time_ms() - philo->data->start;
	if (philo->data->alive)
	{
		philo->data->alive = 0;
		//usleep(1000);
		printf("%lld %d died\n", time_ms, philo->id);
	}
	if (pthread_mutex_unlock(&philo->data->print))
		return (1);
	return (0);
}

int	print_info(t_philo *philo, char *str)
{
	long long	time_ms;

	if (pthread_mutex_lock(&philo->data->print))
		return (1);
	time_ms = get_time_ms() - philo->data->start;
	if (philo->data->alive)
	{
		if (ft_strcmp(str, "pass"))
			printf("%lld %d %s\n", time_ms, philo->id, str);
	}
	if (pthread_mutex_unlock(&philo->data->print))
		return (1);
	return (0);
}

int	check_alive(t_philo *philo)
{
	long long	time_ms;

	time_ms = get_time_ms();
	if (!philo->time_last_meal)
		philo->time_last_meal = get_time_ms() - 1;
	if (!philo->data->alive)
		return (0);
	if (time_ms - philo->time_last_meal > philo->data->time_die)
	{
		print_dead(philo);
		return (0);
	}
	return (1);
}
