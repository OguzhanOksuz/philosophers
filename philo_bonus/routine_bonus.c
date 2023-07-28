/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:56:00 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/28 14:33:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header_bonus.h"

int	rw_val(pthread_mutex_t *lock, int *data, int new_d)
{
	int	rt;

	pthread_mutex_lock(lock);
	if (new_d != 0)
		*data = new_d;
	rt = *data;
	pthread_mutex_unlock(lock);
	return (rt);
}

void	*eat_checker(void *ptr)
{
	t_rules	*rules;
	int		i;

	i = -1;
	rules = (t_rules *)ptr;
	while (++i < rules->p_count)
		sem_wait(rules->eaten);
	sem_post(rules->death);
	return (0);
}

void	*reaper(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if ((get_time() - rw_val(&philo->read, &philo->last_eat, 0))
			> rw_val(&philo->read, &philo->rules->death_t, 0))
		{
			ft_print(DIE, philo);
			sem_post(philo->rules->death);
			break ;
		}
		u_sleep(1);
	}
	return (0);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->death, NULL, reaper, philo);
	pthread_detach(philo->death);
	while (1)
	{
		sem_wait(philo->rules->forks);
		ft_print(FORK, philo);
		sem_wait(philo->rules->forks);
		ft_print(FORK, philo);
		ft_print(EAT, philo);
		rw_val(&philo->read, &philo->last_eat, get_time());
		rw_val(&philo->read, &philo->eat_count,
			(rw_val(&philo->read, &philo->eat_count, 0) + 1));
		if (rw_val(&philo->read, &philo->eat_count, 0) == rw_val(&philo->read,
				&philo->rules->max_eat, 0))
			sem_post(philo->rules->eaten);
		u_sleep(philo->rules->eat_t);
		sem_post(philo->rules->forks);
		sem_post(philo->rules->forks);
		ft_print(SLEEP, philo);
		u_sleep(philo->rules->sleep_t);
		ft_print(THINK, philo);
	}
}

void	end_program(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->p_count)
		kill(rules->philos[i]->pid, SIGKILL);
	my_free(rules);
}
