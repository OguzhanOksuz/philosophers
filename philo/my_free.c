void	free_rules(t_rules *rules)
{

}

void	free_philos(t_philos **philos)
{

}

t_philo	**philos_error_free(t_philo **philo, int i)
{
	while (i >= 0)
		free(philos[i--]);
	free(philos);
	return (NULL);
}
