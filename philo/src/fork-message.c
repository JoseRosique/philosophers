/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork-message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:35:31 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/22 02:23:06 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_clean_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->p_forks[LEFT]);
	pthread_mutex_unlock(philo->p_forks[RIGHT]);
	return ;
}

int	philo_take_forks(t_philo *philo)
{
	int	side;

	if (philo->seat % 2 == 0)
		side = LEFT;
	else
		side = RIGHT;
	if (lock_check(philo, philo->p_forks[side], "philo_take_forks") != 0)
		return (1);
	status_change_message(philo, MSG_FORK, FORK);
	if (lock_check(philo, philo->p_forks[!side], "philo_take_forks") != 0)
	{
		pthread_mutex_unlock(philo->p_forks[side]);
		return (1);
	}
	status_change_message(philo, MSG_FORK, FORK);
	return (0);
}

int	set_dead(t_philo *philo)
{
	if (lock_check(philo, &philo->setup->dead_lock, "set_dead") != 0)
		return (1);
	philo->setup->someone_dead = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (0);
}

void	print_message(t_philo *philo, const char *message, t_msg_type type)
{
	uintmax_t	time;

	time = retrieve_time_since_ms(philo->setup->program_start_ms);
	printf("%s", get_philo_colour(philo->seat));
	printf("%jums\tphilo [%d] %s.", time, philo->seat, message);
	if (philo->setup->must_eat && type == EAT)
		printf(" (%d/%d)", philo->times_eaten + 1, philo->setup->must_eat);
	printf("\n%s", WHT);
}

int	status_change_message(t_philo *philo, const char *message, t_msg_type type)
{
	if (lock_check(philo, &philo->setup->msg_lock,
			"status_change_message") != 0)
		return (1);
	if (!gameover(philo))
	{
		print_message(philo, message, type);
		if (type == DEAD)
			set_dead(philo);
	}
	pthread_mutex_unlock(&philo->setup->msg_lock);
	return (0);
}
