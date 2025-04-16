/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:05 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/16 14:28:57 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	int	i;
	
	i = 0;
	philo = (t_philo *)arg;
	while(i < 5)
	{
		think(*philo);
		take_fork(*philo);
		eat(*philo);
		release_fork(*philo);
		philo_sleep(*philo);
		i++;
	}
	return(NULL);
}

void	master_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->data->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while(i < philo->data->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
