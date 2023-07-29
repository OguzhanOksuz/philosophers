/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:33:06 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/29 18:11:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_free(t_rules *rules)
{
	int	i;

	if (rules->philos)
	{
		i = -1;
		while (++i < rules->p_count)
		{
			pthread_join(rules->philos[i]->p_thread, NULL);
			free(rules->philos[i]);
		}
	}
	i = -1;
	while (++i < rules->p_count)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->last_eat_m[i]);
	}
	pthread_mutex_destroy(&rules->eat_t_m);
	pthread_mutex_destroy(&rules->sleep_t_m);
	pthread_mutex_destroy(&rules->max_eat_m);
	pthread_mutex_destroy(&rules->eaten_m);
	pthread_mutex_destroy(&rules->is_death_m);
	pthread_mutex_destroy(&rules->print_m);
	free(rules->forks);
	free(rules->last_eat_m);
}

t_philo	**philos_error_free(t_philo **philos, int i)
{
	while (i >= 0)
		free(philos[i--]);
	free(philos);
	return (NULL);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * (rules->p_count));
	if (!rules->forks)
		return (0);
	rules->last_eat_m = malloc(sizeof(pthread_mutex_t) * (rules->p_count));
	if (!rules->last_eat_m)
		return (free(rules->last_eat_m), 0);
	while (++i < rules->p_count)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		pthread_mutex_init(&rules->last_eat_m[i], NULL);
	}
	pthread_mutex_init(&rules->eat_t_m, NULL);
	pthread_mutex_init(&rules->sleep_t_m, NULL);
	pthread_mutex_init(&rules->max_eat_m, NULL);
	pthread_mutex_init(&rules->eaten_m, NULL);
	pthread_mutex_init(&rules->is_death_m, NULL);
	pthread_mutex_init(&rules->print_m, NULL);
	return (1);
}

t_philo	**init_philos(t_rules *rules)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * (rules->p_count));
	if (!philos)
		return (NULL);
	while (i < rules->p_count)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
			return (philos_error_free(philos, i));
		philos[i]->id = i + 1;
		philos[i]->num = i;
		philos[i]->l_fork = i;
		philos[i]->r_fork = (i + 1) % (rules->p_count);
		philos[i]->eat_count = 0;
		philos[i]->last_eat = get_time();
		philos[i]->rules = rules;
		i++;
	}
	rules->philos = philos;
	return (philos);
}

t_rules	*init_rules(int ac, char **av)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->p_count = ft_atoi(av[1]);
	rules->death_t = ft_atoi(av[2]);
	rules->eat_t = ft_atoi(av[3]);
	rules->sleep_t = ft_atoi(av[4]);
	if (ac == 6)
		rules->max_eat = ft_atoi(av[5]);
	else
		rules->max_eat = -1;
	rules->eaten = 0;
	rules->is_dead = 0;
	init_philos(rules);
	if (!rules->philos)
		return (my_free(rules), NULL);
	rules->mutex = init_mutex(rules);
	if (!rules->mutex)
		return (my_free(rules), NULL);
	rules->start = get_time();
	return (rules);
}
