/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:52:12 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:15 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *philo_create(int philo_amount, pthread_mutex_t *mutex, t_data *data)
{
	int i;
	t_philo *arr;

	i = 0;
	arr = malloc(sizeof(t_philo) * philo_amount);
	if(!arr)
		return(NULL);
	while(i < philo_amount)
	{
		arr[i].id = i;
		arr[i].left_fork = &mutex[i];
		arr[i].right_fork = &mutex[(i + 1) % philo_amount];
		arr[i].data = data;
		i++;
	}
	return(arr);	
}
void	philo_destroy(t_philo *arr)
{
	free(arr);
}