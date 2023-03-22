/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:33:39 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 21:25:12 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h> // intmax_t
# include <pthread.h> // pthread
# include <stdbool.h> // bool
# include <stdint.h> // INT_MAX/MIN
# include <stdio.h> // printf
# include <stdlib.h> // free, malloc
# include <sys/time.h> // gettimeofday
# include <unistd.h> // write, usleep

# define ERR_SETUP "Error: invalid arguments provided\n"
# define ERR_GEN "Error\n"
# define MSG_FORK " has taken a fork"
# define MSG_EAT " is eating"
# define MSG_SLEEP " is sleeping"
# define MSG_THINK " is thinking"
# define MSG_DIED " died"
# define MSG_ENOUGH " has eaten enough"
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

typedef struct s_init
{
	bool		fork_init;
	bool		philos_init;
}				t_init;

typedef struct s_setup
{
	int				num_philo;
	int				msec_to_die;
	int				msec_to_eat;
	int				msec_to_sleep;
	int				must_eat;
	int				full_philos;
	uintmax_t		program_start_ms;
	bool			someone_dead;
	pthread_mutex_t	msg_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	struct s_init	initialized;
}					t_setup;

typedef struct s_philo
{
	pthread_t		id;
	int				seat;
	bool			active;
	int				times_eaten;
	uintmax_t		last_ate_msec;
	uintmax_t		deadline;
	struct s_setup	*setup;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*p_forks[2];
}				t_philo;

// check.c
void		*philo_check(void *philo_arg);

// exit.c
int			print_error(const char *message);
int			clean_exit(t_setup *setup, t_philo **philos);

// fork.c
void		philo_clean_forks(t_philo *philo);
int			philo_take_forks(t_philo *philo);

// init.c
int			init_philos(t_setup *setup, t_philo **philos);
int			init_forks(t_setup *setup);
int			init_philos_and_mutexes(t_setup *setup, t_philo **philos);
void		init_setup(t_setup *setup);

// main.c
int			status_change_message(t_philo *philo, const char *message,
				t_msg_type type);

// philo_utils.c
int			lock_check(t_philo *philo, pthread_mutex_t *lock, const char *fn);
int			update_eat_time(t_philo *philo);
bool		has_eaten_enough(t_philo *philo);
bool		gameover(t_philo *philo);
void		u_sleep_better(uintmax_t usec);

// philo.c
void		*philo_do(void *philo_arg);

// prog_utils.c
const char	*get_philo_colour(int philo_seat);
int			ft_strcmp(void *s1, void *s2);
bool		is_whitespace(const char c);
int			ft_skipws(const char **str, int i);
bool		valid_atoi(const char *num_str, int *num);

// setup.c
int			parse_args_into_setup(t_setup *setup, const char **args);

// time.c
uintmax_t	retrieve_time_us(void);
uintmax_t	retrieve_time_since_ms(uintmax_t start);

#endif //PHILO_H
