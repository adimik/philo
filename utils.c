/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:19:14 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/30 16:06:54 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    data_init(char **argv, t_data *data)
{
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]) * 1000;
    data->time_to_eat = ft_atoi(argv[3]) * 1000;
    data->time_to_sleep = ft_atoi(argv[4]) * 1000;
    data->start_time = time_in_ms();
    data->running = 1;
    pthread_mutex_init(&data->printf_mutex, NULL);
}
int     ft_atoi(char *arr)
{
    int i;
    int num;
    
    i = 0;
    num = 0;
    while(arr[i])
    {
        num = num * 10 + (arr[i] - '0');
        i++;
    }
    return(num);
}
