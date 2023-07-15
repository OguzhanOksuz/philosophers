/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:56:00 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/15 23:58:44 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	routine(t_philo *philo)
{
	while (!philo->is_dead)
	{
		sem_wait(philo->rules->forks);
		ft_print(FORK, philo);
		sem_wait(philo->rules->forks);
		ft_print(FORK, philo);
		ft_print(EAT, philo);
		philo->last_eat = get_time();
		philo->eat_count++;
		u_sleep(philo->rules->eat_t);
		sem_post(philo->rules->forks);
		sem_post(philo->rules->forks);
		ft_print(SLEEP, philo);
		u_sleep(philo->rules->sleep_t);
		ft_print(THINK, philo);
	}
}
/*
void	*reaper(void *ptr)
{

}
*/
void	end_program(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->p_count)
		kill(rules->philos[i++]->pid, SIGKILL);
	my_free(rules);
}
