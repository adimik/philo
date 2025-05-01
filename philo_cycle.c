/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:35 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/01 19:07:59 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	long long	time;
	int			i;

	i = is_running(philo);
	if (i == 0)
		return (0);
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = time_in_ms();
	time = time - philo->data->start_time;
	printf("%lld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (1);
}
int	take_fork(t_philo *philo)
{
	long long	time;
	int			i;

	i = is_running(philo);
	if (i == 0)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if(!is_running(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return(0);
		}
	pthread_mutex_lock(philo->right_fork);
	if(!is_running(philo))
	{
		release_fork(philo);
		return(0);
	}
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = time_in_ms();
	time = time - philo->data->start_time;
	printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (1);
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
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	smart_usleep(philo, philo->data->time_to_eat / 1000);
	return (1);
}
void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
int	philo_sleep(t_philo *philo)
{
	long long time;
	int i;
	
	i = is_running(philo);
	if(i == 0)
		return(0);
	time = time_in_ms();
	time = time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	smart_usleep(philo, philo->data->time_to_sleep / 1000);
	return(1);
}