/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:35 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/30 17:42:16 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	long long	time;

	if (!is_running(philo))
		return (0);
	time = time_in_ms();
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = time - philo->data->start_time;
	if (is_running(philo))
		printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (1);
}

int	take_fork(t_philo *philo)
{
	int	i;

	i = is_running(philo);
	if (i == 0)
		return (0);
	if (philo->id % 2 == 0)
		return (lock_from_left(philo));
	else
		return (lock_from_right(philo));
}

int	eat(t_philo *philo)
{
	long long	time;
	long long	now;
	int			i;

	i = is_running(philo);
	if (i == 0)
		return (0);
	now = time_in_ms();
	time = now - philo->data->start_time;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_of_last_meal = now;
	philo->num_of_eat++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (is_running(philo))
		printf("%lld %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	smart_usleep(philo, philo->data->time_to_eat / 1000);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long long	time;
	int			i;

	i = is_running(philo);
	if (i == 0)
		return (0);
	time = time_in_ms();
	time = time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (is_running(philo))
		printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	smart_usleep(philo, philo->data->time_to_sleep / 1000);
	return (1);
}
