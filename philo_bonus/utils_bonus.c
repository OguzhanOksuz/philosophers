/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:43:42 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/28 14:50:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header_bonus.h"

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
			break ;
		usleep(100);
	}
}

void	ft_print(int code, t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	sem_wait(rules->print);
	if (!philo->is_dead)
	{
		printf("%d ", (get_time() - rules->start));
		printf("%d ", philo->id);
		if (code == FORK)
			printf("has taken a fork\n");
		else if (code == EAT)
			printf("is eating\n");
		else if (code == SLEEP)
			printf("is sleeping\n");
		else if (code == THINK)
			printf("is thinking\n");
		else if (code == DIE)
			printf("died\n");
	}
	if (code != DIE)
		sem_post(rules->print);
}
