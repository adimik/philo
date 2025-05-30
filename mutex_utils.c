/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:29 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/30 17:42:40 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*mutex_malloc(int amount)
{
	pthread_mutex_t	*arr;
	int				i;

	i = 0;
	arr = malloc(amount * sizeof(pthread_mutex_t));
	if (!arr)
		return (NULL);
	while (i < amount)
	{
		pthread_mutex_init(&arr[i], NULL);
		i++;
	}
	return (arr);
}

void	mutex_destroy(pthread_mutex_t *arr, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&arr[i]);
		i++;
	}
	free(arr);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	lock_from_left(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->left_fork);
	if (!is_running(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = time_in_ms() - philo->data->start_time;
	if (is_running(philo))
		printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(philo->right_fork);
	if (!is_running(philo))
	{
		release_fork(philo);
		return (0);
	}
	time = time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (is_running(philo))
		printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (1);
}

int	lock_from_right(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->right_fork);
	if (!is_running(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->data->printf_mutex);
	time = time_in_ms() - philo->data->start_time;
	if (is_running(philo))
		printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_lock(philo->left_fork);
	if (!is_running(philo))
	{
		release_fork(philo);
		return (0);
	}
	time = time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (is_running(philo))
		printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (1);
}
