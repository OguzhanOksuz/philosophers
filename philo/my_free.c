/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:33:22 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/14 01:00:01 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_free(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->p_count)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->read);
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->death);
	free(rules->forks);
	if (rules->philos)
	{
		i = 0;
		while (i < rules->p_count)
			free(rules->philos[i++]);
		free(rules->philos);
	}
	free(rules);
}

t_philo	**philos_error_free(t_philo **philos, int i)
{
	while (i >= 0)
		free(philos[i--]);
	free(philos);
	return (NULL);
}
