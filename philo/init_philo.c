#include "my_header.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * (rules->p_count));
	if (!rules->forks)
		return (0);
	while (i < rules->p_count)
		pthread_mutex_init(&rules->forks[i++], NULL);
	pthread_mutex_init(&rules->read, NULL);
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
		philos[i]->l_fork = i;
		philos[i]->r_fork = (i + 1) % (rules->p_count);
		philos[i]->eat_count = 0;
		philos[i]->last_eat = rules->start;
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
	rules->is_dead = 0;
	rules->eaten = 0;
	rules->start = get_time();
	init_philos(rules);
	if (!rules->philos)
		return (free_rules(rules), NULL);
	rules->mutex = init_mutex(rules);
	if (!rules->mutex)
		return (free_rules(rules), free_philos(rules->philos), NULL);
	return (rules);
}
