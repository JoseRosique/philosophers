/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:36:11 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 18:10:04 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	if (status_change_message(philo, MSG_THINK, THINK))
		return (1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (status_change_message(philo, MSG_SLEEP, SLEEP))
		return (1);
	u_sleep_better(philo->setup->msec_to_sleep * 1000);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (update_eat_time(philo))
		return (1);
	status_change_message(philo, MSG_EAT, EAT);
	u_sleep_better(philo->setup->msec_to_eat * 1000);
	philo->times_eaten++;
	philo_clean_forks(philo);
	return (0);
}

void	*philo_do(void *philo_arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_arg;
	philo->active = true;
	if (pthread_create(&tid, NULL, &philo_check, philo_arg) != 0)
		return ((void *)1);
	if (philo->seat % 2 == 0)
		usleep(1000);
	if (update_eat_time(philo) == 0)
	{
		while (!gameover(philo) && !has_eaten_enough(philo))
		{
			if (philo_take_forks(philo)
				|| philo_eat(philo)
				|| philo_sleep(philo)
				|| philo_think(philo))
				break ;
			usleep(1000);
		}
	}
	philo->active = false;
	pthread_join(tid, NULL);
	return (NULL);
}
