/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:33:47 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/14 02:23:09 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

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

void	eat(t_rules *rules, t_philo *philo, int max_eat, int eat_t)
{
	ft_print(EAT, philo);
	philo->eat_count++;
	if (philo->eat_count == max_eat)
		rw_val(&rules->read, &rules->eaten,
			rw_val(&rules->read, &rules->eaten, 0) + 1);
	rw_val(&rules->read, &philo->last_eat, get_time());
	u_sleep(eat_t);
}

void	*threads(void	*ptr)
{
	t_philo	*philo;
	int		max_eat;
	int		eat_t;
	int		sleep_t;

	philo = (t_philo *)ptr;
	max_eat = rw_val(&philo->rules->read, &philo->rules->max_eat, 0);
	eat_t = rw_val(&philo->rules->read, &philo->rules->eat_t, 0);
	sleep_t = rw_val(&philo->rules->read, &philo->rules->sleep_t, 0);
	if (philo->id % 2)
		u_sleep(eat_t);
	while (!rw_val(&philo->rules->death, &philo->rules->is_dead, 0))
	{
		pthread_mutex_lock(&philo->rules->forks[philo->l_fork]);
		ft_print(FORK, philo);
		pthread_mutex_lock(&philo->rules->forks[philo->r_fork]);
		ft_print(FORK, philo);
		eat(philo->rules, philo, max_eat, eat_t);
		pthread_mutex_unlock(&philo->rules->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork]);
		ft_print(SLEEP, philo);
		u_sleep(sleep_t);
		ft_print(THINK, philo);
	}
	return (NULL);
}

void	reaper(t_rules *rules)
{
	int	i;
	int	p_c;
	int	max_eat;
	int	death_t;

	p_c = rw_val(&rules->read, &rules->p_count, 0);
	max_eat = rw_val(&rules->read, &rules->max_eat, 0);
	death_t = rw_val(&rules->read, &rules->death_t, 0);
	while (!rw_val(&rules->death, &rules->is_dead, 0))
	{
		i = -1;
		while (++i < p_c)
		{
			if (get_time() - rw_val(&rules->read,
					&rules->philos[i]->last_eat, 0) > death_t)
			{
				ft_print(DIE, rules->philos[i]);
				rw_val(&rules->death, &rules->is_dead, 1);
			}
		}
		if (p_c == rw_val(&rules->read, &rules->eaten, 0))
			rw_val(&rules->death, &rules->is_dead, 1);
		u_sleep(10);
	}
	my_free(rules);
}
