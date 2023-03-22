/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:35:04 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/21 18:05:43 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo_threads(t_setup *setup, t_philo *philos)
{
	int			i;

	i = 0;
	while (philos && i < setup->num_philo)
	{
		if (pthread_create(&philos[i].id, NULL, &philo_do,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	setup->program_start_ms = retrieve_time_since_ms(0);
	i = 0;
	while (i < setup->num_philo)
	{
		pthread_join(philos[i].id, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_setup	setup;
	t_philo	*philos;

	if (ac > 4 && ac < 7)
	{
		init_setup(&setup);
		if (parse_args_into_setup(&setup, (const char **)(av + 1)))
			return (print_error(ERR_SETUP) | clean_exit(&setup, NULL));
		if (init_philos_and_mutexes(&setup, &philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		if (start_philo_threads(&setup, philos))
			return (print_error(ERR_GEN) | clean_exit(&setup, &philos));
		clean_exit(&setup, &philos);
	}
	return (0);
}
