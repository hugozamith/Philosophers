/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hteixeir <hteixeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:48:15 by druina            #+#    #+#             */
/*   Updated: 2024/09/06 13:29:55 by hteixeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_message(BOLD_GREEN"is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message(BOLD_YELLOW"is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	mutexxxer(philo->r_fork, LOCK);
	print_message(BOLD_CYAN"has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		mutexxxer(philo->r_fork, UNLOCK);
		return ;
	}
	mutexxxer(philo->l_fork, LOCK);
	print_message(BOLD_CYAN"has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message(BOLD_BLUE"is eating", philo, philo->id);
	mutexxxer(philo->meal_lock, LOCK);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	mutexxxer(philo->meal_lock, UNLOCK);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	mutexxxer(philo->l_fork, UNLOCK);
	mutexxxer(philo->r_fork, UNLOCK);
}
