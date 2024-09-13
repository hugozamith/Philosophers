/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_mtx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hteixeir <hteixeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:04:45 by hteixeir          #+#    #+#             */
/*   Updated: 2024/09/06 13:40:11 by hteixeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutexxxer(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		return (pthread_mutex_lock(mutex));
	else if (UNLOCK == opcode)
		return (pthread_mutex_unlock(mutex));
	else if (INIT == opcode)
		return (pthread_mutex_init(mutex, NULL));
	else if (DESTROY == opcode)
		return (pthread_mutex_destroy(mutex));
	else
		return (0);
}

int	threader(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		return (pthread_create(thread, NULL, foo, data));
	else if (JOIN == opcode)
		return (pthread_join(*thread, NULL));
	else if (DETACH == opcode)
		return (pthread_detach(*thread));
	else
		return (0);
}
