/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:55 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/30 14:22:13 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long long   start_time;
    pthread_mutex_t printf_mutex;
    int running;
    pthread_mutex_t running_mutex;
}t_data;

typedef struct s_philo
{
    int id;
    int alive;
    long long time_of_last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_mutex;
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
void	philo_destroy(t_philo *arr, int amount);
void	master_thread(t_philo *philo);
void	*philo_routine(void *arg);
void	think(t_philo *philo);
void	take_fork(t_philo *philo);
void	eat(t_philo *philo);
void	release_fork(t_philo *philo);
void	philo_sleep(t_philo philo);
long long   time_in_ms(void);
long long   time_now(t_philo philo);
void    smart_usleep(t_philo *philo, long long duration);
void	*watchdog(void *arg);

#endif