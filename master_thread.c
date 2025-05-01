/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:05 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/30 16:12:01 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->alive)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		release_fork(philo);
		philo_sleep(*philo);
		//philo->alive = 0;
	}
	return(NULL);
}
void	*watchdog(void *arg)
{
	t_philo *philo;
	int i;
	long long last_meal;
	long long now;

	i = 0;
	philo = (t_philo*)arg;
	while(1)
	{
		while(i < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			last_meal = philo[i].time_of_last_meal;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			now  = time_in_ms();
			if((now - last_meal) > philo->data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->running_mutex);
				philo->data->running = 0;
				pthread_mutex_unlock(&philo->data->running_mutex);
				pthread_mutex_lock(&philo->data->printf_mutex);
				printf("%lld %d died\n", now, philo[i].id);
				pthread_mutex_unlock(&philo->data->printf_mutex);
				return(NULL);
			}
			i++;
			usleep(500);
		}
		i = 0;
	}
}

void	master_thread(t_philo *philo)
{
	pthread_t monitor;
	int	i;

	i = 0;
	while(i < philo->data->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, watchdog, &philo);
	pthread_join(monitor, NULL);
	i = 0;
	while(i < philo->data->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
