/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:55 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/30 17:42:58 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_rep;
	int				num_philo_ate;
	long long		start_time;
	pthread_mutex_t	printf_mutex;
	int				running;
	pthread_mutex_t	running_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				alive;
	int				num_of_eat;
	long long		time_of_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
	pthread_t		thread;
}					t_philo;

pthread_mutex_t		*mutex_malloc(int amount);
void				mutex_destroy(pthread_mutex_t *arr, int amount);
int					ft_atoi(char *arr);
int					data_init(char **argv, t_data *data, int argc);
t_philo				*philo_create(int philo_amount, pthread_mutex_t *mutex,
						t_data *data);
void				philo_destroy(t_philo *arr, int amount);
void				master_thread(t_philo *philo);
void				*philo_routine(void *arg);
int					think(t_philo *philo);
int					eat(t_philo *philo);
void				release_fork(t_philo *philo);
int					philo_sleep(t_philo *philo);
long long			time_in_ms(void);
long long			time_now(t_philo philo);
int					smart_usleep(t_philo *philo, long long duration);
void				*watchdog(void *arg);
int					is_running(t_philo *philo);
void				philo_dead(long long now, int id, t_philo *philo);
int					philo_checker(t_philo *philo, int id);
void				end_simulation(t_philo *philo);
int					valid_positive_input(t_data *data, int argc);
int					take_fork(t_philo *philo);
int					lock_from_right(t_philo *philo);
int					lock_from_left(t_philo *philo);

#endif