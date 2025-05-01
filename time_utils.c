/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:06:44 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/01 19:36:56 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long   time_in_ms(void)
{
    struct timeval t;
    long long time;
    
    gettimeofday(&t, NULL);
    time = ((long long)t.tv_sec * 1000 + t.tv_usec / 1000);
    return(time);
}
long long   time_now(t_philo philo)
{
	long long time;
	
	time = time_in_ms();
	time = time - philo.data->start_time;
    return(time);
}

int    smart_usleep(t_philo *philo, long long duration)
{
    long long start;
    long long now;
    int i;
	
	i = is_running(philo);
	if(i == 0)
		return(0);
    start = time_in_ms();
    now = time_in_ms();
    while(now - start < duration)
    {
        if(!is_running(philo))
            return(0);
        usleep(20);
        now = time_in_ms();
    }
    return(1);
}