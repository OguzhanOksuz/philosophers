/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:54:03 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/27 19:48:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_free(t_rules *rules)
{
	int	i;

	if (rules->philos)
	{
		i = 0;
		while (i < rules->p_count)
		{
			sem_post(rules->eaten);
			free(rules->philos[i++]);
		}
		free(rules->philos);
	}
	sem_close(rules->forks);
	sem_close(rules->print);
	sem_close(rules->eaten);
	sem_close(rules->death);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eaten");
	sem_unlink("death");
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
		pthread_mutex_init(&philos[i]->read, NULL);
		i++;
	}
	rules->philos = philos;
	return (philos);
}

int	init_sem(t_rules *rules)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eaten");
	sem_unlink("death");
	rules->forks = sem_open("forks", O_CREAT, 0666, rules->p_count);
	rules->print = sem_open("print", O_CREAT, 0666, 1);
	rules->eaten = sem_open("eaten", O_CREAT, 0666, 0);
	rules->death = sem_open("death", O_CREAT, 0666, 0);
	return (0);
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
	init_sem(rules);
	return (rules);
}
