/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:55 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/03 21:48:12 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}t_data;

typedef struct s_philo
{
    pthread_mutex_t fork;
}t_philo;


// MUTEX_UTILS.C
pthread_mutex_t *mutex_malloc(int amount);
void    mutex_destroy(pthread_mutex_t *arr, int amount);
//UTILS.C
int     ft_atoi(char *arr);
void    data_init(char **argv, t_data *data);

#endif