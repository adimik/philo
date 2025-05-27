/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:19:14 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/27 19:43:32 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(char **argv, t_data *data, int argc)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->start_time = time_in_ms();
	data->running = 1;
	data->num_philo_ate = 1;
	if (argc == 6)
	{
		data->num_of_rep = ft_atoi(argv[5]);
	}
	else
		data->num_of_rep = -1;
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->running_mutex, NULL);
	if (!valid_positive_input(data, argc))
		return (0);
	return (1);
}

int	valid_positive_input(t_data *data, int argc)
{
	if (data->number_of_philosophers < 1)
		return (0);
	if (data->time_to_die < 1)
		return (0);
	if (data->time_to_eat < 1)
		return (0);
	if (data->time_to_sleep < 1)
		return (0);
	if (data->num_of_rep < 1 && argc == 6)
		return (0);
	return (1);
}

int	ft_atoi(char *arr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (arr[i])
	{
		num = num * 10 + (arr[i] - '0');
		i++;
	}
	return (num);
}

void	philo_dead(long long now, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->running_mutex);
	philo->data->running = 0;
	pthread_mutex_unlock(&philo->data->running_mutex);
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%lld %d died\n", now - philo->data->start_time, philo[id].id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

int	philo_checker(t_philo *philo, int id)
{
	long long	last_meal;
	long long	now;
	int			num_of_eat;

	pthread_mutex_lock(&philo[id].meal_mutex);
	last_meal = philo[id].time_of_last_meal;
	num_of_eat = philo[id].num_of_eat;
	pthread_mutex_unlock(&philo[id].meal_mutex);
	now = time_in_ms();
	if ((now - last_meal) > philo->data->time_to_die / 1000)
	{
		philo_dead(now, id, philo);
		return (0);
	}
	if (num_of_eat >= philo->data->num_of_rep && philo->data->num_of_rep > 0)
		return (2);
	return (1);
}
