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

t_philo				*init_philos(int argc, char **argv);

void				*actions(void *void_philo);

#endif