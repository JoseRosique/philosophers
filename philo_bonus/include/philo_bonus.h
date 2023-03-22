/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:33:39 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/22 02:57:51 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define ERR_SETUP "Error: invalid arguments provided\n"
# define ERR_PAR "Error parsing\n"
# define ERR_THDS "Error creating threads.\n"
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED " died"
# define MSG_ENOUGH "has eaten enough"
# define LEFT 0
# define RIGHT 1

# define DEBUG 0

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define BLK "\e[0;30m"

typedef enum e_msg_type {
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	ENOUGH
}			t_msg_type;

typedef struct s_const
{
	int					id;
	int					ate;
	int					dead_philo;
	unsigned long		time_last_eat;
	pthread_t			*philo_thread;
	struct s_philo		*var;
}t_const_philo;

typedef struct s_philo
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					dead;
	int					*pid;
	unsigned long		time_birth;
	sem_t				*fork;
	sem_t				*act;
	t_const_philo		*var;
}	t_philo;

int				doo(t_philo *philo);
void			destroy_sem(t_philo *philo);
void			*check_death(t_const_philo *philo);
void			process_kill(t_philo *param);
void			create_process(t_philo *philo, int *pid);
int				init_var(t_philo *philo, char **av);
int				init_sema(t_philo *philo);
void			*philos_process(t_philo *philos, int i);
void			life(t_const_philo *philo);
void			philo_eat(t_const_philo *philo);
void			philo_do(t_const_philo *philo, int id, char *str);
void			my_sleep(long long time, t_philo *data);
long long		m_time(long long past, long long pres);
unsigned long	timestamp(void);
int				ft_atoi(char *str);

#endif
