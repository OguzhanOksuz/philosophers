#include "my_header.h"

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	return (num);
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	u_sleep(int time)
{
	int	i;

	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break;
		usleep(100);
	}
}

void	ft_print(int code, t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (!rw_val(&rules->read, &rules->is_dead, 0))
	{
		printf("%d ", (get_time() - rw_val(&rules->read, &rules->start, 0)));
		printf("%d ", rw_val(&rules->read, &philo->id, 0) + 1);
		if (code == FORK)
			printf("has taken a fork\n");
		else if (code == EAT)
			printf("has eating\n");
		else if (code == SLEEP)
			printf("is sleeping\n");
		else if (code == THINK)
			printf("is thinking\n");
		else if (code == DIE)
			printf("died\n");
	}
}
