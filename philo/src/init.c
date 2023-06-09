/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:33:15 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 18:05:28 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo_mutexes(int idx, t_philo *philo, pthread_mutex_t *locks,
			pthread_mutex_t **p_locks)
{
	p_locks[LEFT] = &locks[idx];
	if (idx == philo->setup->num_philo - 1)
		p_locks[RIGHT] = &locks[0];
	else
		p_locks[RIGHT] = &locks[idx + 1];
	return ;
}

int	init_philos(t_setup *setup, t_philo **philos)
{
	int				i;

	i = 0;
	*philos = NULL;
	*philos = malloc(sizeof(t_philo) * setup->num_philo);
	if (*philos == NULL)
		return (1);
	while (i < setup->num_philo)
	{
		(*philos)[i].id = NULL;
		(*philos)[i].seat = i + 1;
		(*philos)[i].active = false;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].last_ate_msec = retrieve_time_since_ms(0);
		(*philos)[i].deadline = (*philos)[i].last_ate_msec + setup->msec_to_die;
		(*philos)[i].setup = setup;
		if (pthread_mutex_init(&(*philos)[i].eat_lock, NULL) != 0)
			return (1);
		set_philo_mutexes(i, &(*philos)[i], setup->forks, (*philos)[i].p_forks);
		i++;
	}
	setup->initialized.philos_init = 1;
	return (0);
}

int	init_forks(t_setup *setup)
{
	int	i;

	i = 0;
	setup->forks = malloc(sizeof(pthread_mutex_t) * setup->num_philo);
	if (setup->forks == NULL)
		return (1);
	while (i < setup->num_philo)
	{
		if (pthread_mutex_init(&(setup->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	setup->initialized.fork_init = 1;
	return (0);
}

int	init_philos_and_mutexes(t_setup *setup, t_philo **philos)
{
	if (init_forks(setup))
		return (1);
	if (init_philos(setup, philos))
		return (1);
	return (0);
}

void	init_setup(t_setup *setup)
{
	setup->num_philo = 0;
	setup->msec_to_die = 0;
	setup->msec_to_eat = 0;
	setup->msec_to_sleep = 0;
	setup->must_eat = 0;
	setup->full_philos = 0;
	setup->program_start_ms = retrieve_time_since_ms(0);
	setup->someone_dead = false;
	if (pthread_mutex_init(&setup->msg_lock, NULL) != 0)
		return ;
	if (pthread_mutex_init(&setup->dead_lock, NULL) != 0)
		return ;
	setup->initialized.fork_init = false;
	setup->initialized.philos_init = false;
	return ;
}
