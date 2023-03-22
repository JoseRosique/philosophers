/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:34:42 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 18:22:57 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_full_philo(t_philo *philo)
{
	status_change_message(philo, MSG_ENOUGH, ENOUGH);
	philo->setup->full_philos++;
	return (NULL);
}

void	*handle_death(t_philo *philo)
{
	status_change_message(philo, MSG_DIED, DEAD);
	pthread_mutex_unlock(&philo->eat_lock);
	philo_clean_forks(philo);
	return (NULL);
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	uintmax_t	current_time;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (!philo->active)
			break ;
		if (lock_check(philo, &philo->eat_lock, "philo_check") != 0)
			return ((void *)1);
		current_time = retrieve_time_since_ms(0);
		if (current_time > philo->deadline)
			return (handle_death(philo));
		pthread_mutex_unlock(&philo->eat_lock);
		if (philo->setup->must_eat > 0 && has_eaten_enough(philo))
			return (handle_full_philo(philo));
		usleep(1000);
	}
	return (NULL);
}
