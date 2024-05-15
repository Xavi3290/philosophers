/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:04:13 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/15 15:38:09 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleap;
	int				num_to_eat;
	int				alive;
	long long		start;
	pthread_mutex_t	*fork;
	int				*list;
	pthread_mutex_t	print;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	long long		time_last_meal;
	int				num_eat;
}					t_philo;

int					ft_atoi(const char *str);
long long			get_time_ms(void);
int					print_dead(t_philo *philo);
int					print_info(t_philo *philo, char *str);
int					check_alive(t_philo *philo);

t_philo				*init_philos(int argc, char **argv);
void				modify_list(t_data *data, int id);

void				*actions(void *void_philo);
int					ft_strcmp(const char *s1, const char *s2);

#endif