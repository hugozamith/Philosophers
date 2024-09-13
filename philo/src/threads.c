/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hteixeir <hteixeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2024/09/06 10:05:33 by hteixeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	mutexxxer(philo->dead_lock, LOCK);
	if (*philo->dead == 1)
		return (mutexxxer(philo->dead_lock, UNLOCK), 1);
	mutexxxer(philo->dead_lock, UNLOCK);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (threader(&observer, &monitor, program->philos, CREATE) != 0)
		destory_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (threader(&program->philos[i].thread, &philo_routine,
				&program->philos[i], CREATE) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (threader(&observer, NULL, NULL, JOIN) != 0)
		destory_all("Thread join error", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (threader(&program->philos[i].thread, NULL, NULL, JOIN) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}
