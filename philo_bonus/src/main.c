/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:35:04 by joslopez          #+#    #+#             */
/*   Updated: 2023/03/22 02:57:40 by joslopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_error(int err)
{
	if (err == 1)
		printf(ERR_SETUP);
	else if (err == 2)
		printf(ERR_PAR);
	else if (err == 3)
		printf(ERR_THDS);
	return ;
}

void	destroy_sem(t_philo *philo)
{
	sem_close(philo->fork);
	sem_close(philo->act);
	sem_unlink("philo_forks");
	sem_unlink("philo_action");
}

int	doo(t_philo *philo)
{
	int		i;

	i = 0;
	philo->pid = malloc(sizeof(int) * philo->nb_philos);
	if (!philo->pid)
		return (0);
	create_process(philo, philo->pid);
	while (i < philo->nb_philos)
	{
		waitpid(philo->pid[i++], 0, 0);
	}
	process_kill(philo);
	destroy_sem(philo);
	return (1);
}

int	init_var(t_philo *philo, char **av)
{
	philo->nb_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->dead = 0;
	philo->time_birth = timestamp();
	if (philo->nb_philos < 1 || philo->time_to_die < 1
		|| philo->time_to_eat < 0
		|| philo->time_to_sleep < 0)
		return (0);
	if (av[5])
	{
		philo->nb_must_eat = ft_atoi(av[5]);
		if (philo->nb_must_eat <= 0)
			return (0);
	}
	else
		philo->nb_must_eat = -1;
	if (!init_sema(philo))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
		return (print_error(1), 0);
	if (!(init_var(&philo, av)))
		return (print_error(2), 0);
	if (!(doo(&philo)))
		return (print_error(3), 0);
	return (1);
}
