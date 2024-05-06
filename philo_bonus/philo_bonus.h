/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:29 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/06 19:35:02 by xavi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			philo_num;
	int			time_die;
	int			time_eat;
	int			time_sleap;
	int			num_to_eat;
	int			alive;
	long long	start;
	sem_t		*fork;
	int			*list;
	sem_t		*print;
	sem_t		*sem_alive;
	sem_t		*sem_eat;
}				t_data;

typedef struct s_philo
{
	int			id;
	t_data		*data;
	long long	time_last_meal;
	int			num_eat;
	pid_t		pid;
}				t_philo;

int				ft_atoi(const char *str);
long long		get_time_ms(void);
int				print_dead(t_philo *philo);
int				print_info(t_philo *philo, char *str);
int				check_alive(t_philo *philo);

t_philo			*init_philos(int argc, char **argv);
void			*is_alive(void *v_philo);

int				do_actions(t_philo *philo);

#endif
