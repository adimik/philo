/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: didimitr <didimitr@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:24:52 by didimitr          #+#    #+#             */
/*   Updated: 2025/05/16 13:21:17 by didimitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (argc != 5 && argc != 6)
		return (write(2, "ERROR", 5));
	if (argv[1][0] == '1' && argv[1][1] == '\0')
		return (printf("0 %d died", ft_atoi(argv[2])));
	forks = NULL;
	if (!data_init(argv, &data, argc))
		return(write(2, "ERROR: input cant be negative\n", 31));
	forks = mutex_malloc(data.number_of_philosophers);
	philo = philo_create(data.number_of_philosophers, forks, &data);
	master_thread(philo);
	philo_destroy(philo, data.number_of_philosophers);
	mutex_destroy(forks, data.number_of_philosophers);
	return (0);
}
