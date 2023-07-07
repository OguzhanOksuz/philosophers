#include "my_header.h"

t_philo	**init_philos(t_rules *rules)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo) * (rules->p_count));
	if (!philos)
		return (NULL);
	while (i < rules->p_count)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philos[i])
		{
		}
		philos[i]->id = i;
		philos[i]->eat_count= 0;
		philos[i]->last_eat= 0;
		philos[i]->rules= rules;

	}
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
	rules->eat_limit = 0;
	init_philos(rules);
	if (!rules->philos)
		return (free_rules(rules), NULL);	
	init_mutex(rules);
	if (!rules->mutex)
		return (free_rules(rules), free_philos(rules->philos), NULL);	
	return (rules);
}
