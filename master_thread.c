/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:05 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/14 19:15:44 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_function(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	printf("%d\n", philo->id);
	return(NULL);
}

void	master_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->data->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, test_function, &philo[i]);
		i++;
	}
}