/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:36:11 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 18:09:16 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_check(t_philo *philo, pthread_mutex_t *lock, const char *fn)
{
	if (pthread_mutex_lock(lock) != 0)
	{
		printf("philo [%d] | FAILED to lock in %s\n", philo->seat, fn);
		return (1);
	}
	return (0);
}

int	update_eat_time(t_philo *philo)
{
	if (lock_check(philo, &philo->eat_lock, "update_eat_time") != 0)
		return (1);
	philo->last_ate_msec = retrieve_time_since_ms(0);
	philo->deadline = philo->last_ate_msec + philo->setup->msec_to_die;
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

bool	has_eaten_enough(t_philo *philo)
{
	bool	enough;

	enough = false;
	if (lock_check(philo, &philo->eat_lock, "has_eaten_enough") != 0)
		return (1);
	if (philo->setup->must_eat > 0
		&& philo->times_eaten == philo->setup->must_eat)
		enough = true;
	pthread_mutex_unlock(&philo->eat_lock);
	return (enough);
}

bool	gameover(t_philo *philo)
{
	bool	done;

	done = false;
	if (lock_check(philo, &philo->setup->dead_lock, "gameover") != 0)
		return (1);
	if (philo->setup->someone_dead == true
		|| philo->setup->full_philos == philo->setup->num_philo)
		done = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (done);
}

/* reduces unreliability of usleep by sleeping in smaller increments */

void	u_sleep_better(uintmax_t usec)
{
	uintmax_t	start;

	start = retrieve_time_us();
	while (retrieve_time_us() - start < usec)
		usleep(100);
}
