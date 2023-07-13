/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:33:22 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/11 00:33:23 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	free_rules(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->p_count)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->read);
	free(rules);
}

void	free_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (0 < &philos[i]->rules->p_count)
		free(philos[i++]);
	free(philos);
}

t_philo	**philos_error_free(t_philo **philos, int i)
{
	while (i >= 0)
		free(philos[i--]);
	free(philos);
	return (NULL);
}
