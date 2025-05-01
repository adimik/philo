/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:35 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/30 20:30:51 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	long long time;
	
	time = time_in_ms();
	time = time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d is thinking\n",time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	usleep(500000);
}
void	take_fork(t_philo *philo)
{
	long long time;
	
	time = time_in_ms();
	time = time - philo->data->start_time;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d has taken a fork\n",time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}
void	eat(t_philo *philo)
{
	long long time;
	long long now;
	
	now = time_in_ms();
	time = now - philo->data->start_time;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_of_last_meal = now;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d is eating\n",time ,philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	usleep(philo->data->time_to_eat);
}
void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void	philo_sleep(t_philo philo)
{
	long long time;
	
	time = time_in_ms();
	time = time - philo.data->start_time;
	printf("%lld %d is sleeping\n", time, philo.id);
	usleep(philo.data->time_to_sleep);
}