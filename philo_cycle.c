/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:35 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/16 14:29:23 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo philo)
{
	printf("Philo %d is thinking\n", philo.id);
	usleep(500000);
}
void	take_fork(t_philo philo)
{
		
	pthread_mutex_lock(philo.left_fork);
	pthread_mutex_lock(philo.right_fork);
	printf("philo %d locked forks\n", philo.id);
	// else
	// {
	// 	pthread_mutex_lock(philo.right_fork);
	// 	pthread_mutex_lock(philo.left_fork);
	// 	printf("philo %d locked forks", philo.id);
	// }
}
void	eat(t_philo philo)
{
	printf("Philo %d, is eating\n", philo.id);
	usleep(philo.data->time_to_eat);
}
void	release_fork(t_philo philo)
{
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	printf("philo %d released forks\n", philo.id);
}
void	philo_sleep(t_philo philo)
{
	printf("Philo %d, is sleeping\n", philo.id);
	usleep(philo.data->time_to_sleep);
}