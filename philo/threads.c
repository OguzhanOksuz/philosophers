void	*threads(void	*ptr)
{
	t_philo	*philo;
	int		max_eat;
	int		eat_t;
	int		sleep_t;

	philo = (t_philo *)ptr;
	max_eat = rw_val(&philo->rules->read, &philo->rules->max_eat, NULL);
	eat_t = rw_val(&philo->rules->read, &philo->rules->eat_t, NULL);
	sleep_t = rw_val(&philo->rules->read, &philo->rules->sleep_t, NULL);
	if (philo->id % 2)
		u_sleep(50);
	while (!rw_val(&philo->rules->is_dead, &philo->rules->is_dead, NULL))
	{
		pthread_mutex_lock(&philo->rules->forks[philo->l_fork]);
		ft_print(FORK, philo);
		pthread_mutex_lock(&philo->rules->forks[philo->r_fork]);
		ft_print(FORK, philo);
		eat(philo->rules, philo, max_eat, eat_time);
		pthread_mutex_unlock(&philo->rules->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork]);
		ft_print(SLEEP, philo);
		u_sleep(sleep_t);
	}
}

void	eat(t_rules *rules, t_philo *philo, int max_eat, int eat_t)
{
	ft_print(EAT, philo);
	philo->eat_count++;
	if (philo->eat_count == max_eat)
		rw_val(&rules->read, &rules->eaten,
			rw_val(&rules->read, &rules->eaten, NULL) + 1);
	rw_val(&rules->read, &philo->last_eat, get_time());
	u_sleep(eat_time);
}
