/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:36:11 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/22 02:53:35 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	philo_eat(t_const_philo *philo)
{
	sem_wait(philo->var->fork);
	philo_do(philo, philo->id, MSG_FORK);
	sem_wait(philo->var->fork);
	philo_do(philo, philo->id, MSG_FORK);
	philo_do(philo, philo->id, MSG_EAT);
	my_sleep(philo->var->time_to_eat, philo->var);
	philo->time_last_eat = timestamp();
	sem_post(philo->var->fork);
	sem_post(philo->var->fork);
	philo->ate++;
}

void	life(t_const_philo *philo)
{
	while (!philo->dead_philo && philo->ate != philo->var->nb_must_eat)
	{
		philo_eat(philo);
		philo_do(philo, philo->id, MSG_SLEEP);
		my_sleep(philo->var->time_to_sleep, philo->var);
		philo_do(philo, philo->id, MSG_THINK);
	}
}

void	*philos_process(t_philo *philos, int i)
{
	t_const_philo	philo;

	philo.var = philos;
	philo.id = i + 1;
	philo.dead_philo = 0;
	philo.ate = 0;
	philo.time_last_eat = timestamp();
	pthread_create(philo.philo_thread, NULL, (void *)check_death, &philo);
	life(&philo);
	pthread_detach(*philo.philo_thread);
	return (NULL);
}

int	init_sema(t_philo *philo)
{
	sem_unlink("philo_forks");
	sem_unlink("philo_action");
	philo->fork = sem_open("philo_forks", O_CREAT, 0700, philo->nb_philos);
	philo->act = sem_open("philo_action", O_CREAT, 0700, 1);
	if (philo->fork == SEM_FAILED
		|| philo->act == SEM_FAILED)
	{
		destroy_sem(philo);
		return (0);
	}
	return (1);
}
