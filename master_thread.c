/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:05 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/17 17:20:16 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		running;

	philo = (t_philo *)arg;
	running = is_running(philo);
	while (running)
	{
		if (philo->id % 2 != 0)
			usleep(10);
		if (!take_fork(philo))
			break ;
		if (!eat(philo))
		{
			release_fork(philo);
			break ;
		}
		release_fork(philo);
		if (!philo_sleep(philo))
			break ;
		if (!think(philo))
			break ;
		running = is_running(philo);
	}
	return (NULL);
}

int	is_running(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->running_mutex);
	i = philo->data->running;
	pthread_mutex_unlock(&philo->data->running_mutex);
	return (i);
}

void	*watchdog(void *arg)
{
	t_philo	*philo;
	int		i;
	int		all_ate;
	int		alive;

	philo = (t_philo *)arg;
	while (1)
	{
		all_ate = 0;
		i = 0;
		while (i < philo->data->number_of_philosophers)
		{
			alive = philo_checker(philo, i);
			if (alive == 0)
				return (NULL);
			all_ate += (alive == 2);
			i++;
		}
		if (all_ate == philo->data->number_of_philosophers)
		{
			end_simulation(philo);
			return (NULL);
		}
		usleep(500);
	}
}

void	master_thread(t_philo *philo)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < philo->data->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, watchdog, philo);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < philo->data->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
