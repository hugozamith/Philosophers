/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hteixeir <hteixeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:22:47 by druina            #+#    #+#             */
/*   Updated: 2024/09/06 13:28:35 by hteixeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	mutexxxer(philo->write_lock, LOCK);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf(RST"%zu %d %s\n", time, id, str);
	mutexxxer(philo->write_lock, UNLOCK);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	mutexxxer(philo->meal_lock, LOCK);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (mutexxxer(philo->meal_lock, UNLOCK), 1);
	mutexxxer(philo->meal_lock, UNLOCK);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message(BOLD_RED"DIED", &philos[i], philos[i].id);
			mutexxxer(philos[0].dead_lock, LOCK);
			*philos->dead = 1;
			mutexxxer(philos[0].dead_lock, UNLOCK);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		mutexxxer(philos[i].meal_lock, LOCK);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		mutexxxer(philos[i].meal_lock, UNLOCK);
		i++;
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		mutexxxer(philos[0].dead_lock, LOCK);
		*philos->dead = 1;
		mutexxxer(philos[0].dead_lock, UNLOCK);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
