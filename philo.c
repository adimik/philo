/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:24:52 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/21 14:54:46 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    pthread_mutex_t *forks;
    t_philo *philo;

    if(argc != 5)
        return(write(2, "ERROR", 5));
    forks = NULL;
    data_init(argv, &data);
    forks = mutex_malloc(data.number_of_philosophers);
    philo = philo_create(data.number_of_philosophers, forks, &data);
    master_thread(philo);
    //usleep(1000000);
    philo_destroy(philo, data.number_of_philosophers);
    mutex_destroy(forks, data.number_of_philosophers);
    return(0);
}
