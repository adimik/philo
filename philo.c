/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:24:52 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/03 21:54:02 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    pthread_mutex_t *forks;

    if(argc != 5)
        return(write(2, "ERROR", 5));
    forks = NULL;
    data_init(argv, &data);
    forks = mutex_malloc(data.number_of_philosophers);
    


    mutex_destroy(forks, data.number_of_philosophers);
    return(0);
}
