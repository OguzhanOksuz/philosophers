/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:54:03 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/15 17:44:51 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_free(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->philos)
	{
		i = 0;
		while (i < rules->p_count)
			free(rules->philos[i++]);
		free(rules->philos);
	}
	sem_close(rules->forks);
	sem_close(rules->print);
	sem_close(rules->death);
	free(rules);
}

t_philo	**philos_error_free(t_philo **philos, int i)
{
	while (i >= 0)
		free(philos[i--]);
	free(philos);
	return (NULL);
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
		philos[i]->is_dead = 0;
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
	init_philos(rules);
	if (!rules->philos)
		return (my_free(rules), NULL);
	rules->forks = sem_open("forks", O_CREAT, 0666, rules->p_count);
	rules->print = sem_open("print", O_CREAT, 0666, 1);
	rules->death = sem_open("death", O_CREAT, 0666, 1);
	return (rules);
}
