/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:55 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/14 18:44:01 by didimitr         ###   ########.fr       */
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
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data  *data;
    pthread_t thread;
}t_philo;

// MUTEX_UTILS.C
pthread_mutex_t *mutex_malloc(int amount);
void    mutex_destroy(pthread_mutex_t *arr, int amount);
//UTILS.C
int     ft_atoi(char *arr);
void    data_init(char **argv, t_data *data);

t_philo *philo_create(int philo_amount, pthread_mutex_t *mutex, t_data *data);
void	philo_destroy(t_philo *arr);
void	master_thread(t_philo *philo);
void	*test_function(void *arg);

#endif