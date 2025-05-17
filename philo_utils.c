/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:52:12 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/17 15:03:10 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_create(int philo_amount, pthread_mutex_t *mutex, t_data *data)
{
	int		i;
	t_philo	*arr;

	i = 0;
	arr = malloc(sizeof(t_philo) * philo_amount);
	if (!arr)
		return (NULL);
	while (i < philo_amount)
	{
		arr[i].id = i;
		arr[i].left_fork = &mutex[i];
		arr[i].right_fork = &mutex[(i + 1) % philo_amount];
		arr[i].data = data;
		arr[i].alive = 1;
		arr[i].time_of_last_meal = data->start_time;
		arr[i].num_of_eat = 0;
		pthread_mutex_init(&arr[i].meal_mutex, NULL);
		i++;
	}
	return (arr);
}

void	philo_destroy(t_philo *arr, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&arr[i].meal_mutex);
		i++;
	}
	free(arr);
}

void	end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->running_mutex);
	philo->data->running = 0;
	pthread_mutex_unlock(&philo->data->running_mutex);
}
