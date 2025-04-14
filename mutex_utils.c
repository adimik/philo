/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:32:29 by didimitr          #+#    #+#             */
/*   Updated: 2025/04/03 19:12:38 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *mutex_malloc(int amount)
{
    pthread_mutex_t *arr;
    int i;

    i = 0;
    arr = malloc(amount * sizeof(pthread_mutex_t));
    if (!arr)
        return(NULL);
    while(i < amount)
    {
        pthread_mutex_init(&arr[i], NULL);
        i++;
    }
    return(arr);
}
void    mutex_destroy(pthread_mutex_t *arr, int amount)
{
    int i;

    i = 0;
    while(i < amount)
    {
        pthread_mutex_destroy(&arr[i]);
        i++;
    }
    free(arr);
}