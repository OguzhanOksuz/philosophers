/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 02:11:46 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/28 14:32:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header_bonus.h"

int	is_in_range(char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	if (num > 0 && num <= 2147483647)
		return (1);
	return (0);
}

int	is_all_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	is_av_valid(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		if (is_all_num(av[i]) == 0)
			return (0);
		else
			if (is_in_range(av[i]) == 0)
				return (0);
		i++;
	}
	return (1);
}

void	forker(t_rules *rules)
{
	int		i;

	i = -1;
	while (++i < rules->p_count)
	{
		rules->philos[i]->pid = fork();
		if (rules->philos[i]->pid == 0)
		{
			routine(rules->philos[i]);
			exit(0);
		}
	}
	pthread_create(&rules->eat_check, NULL, eat_checker, rules);
	pthread_detach(rules->eat_check);
	sem_wait(rules->death);
	end_program(rules);
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	if (is_av_valid(ac, av))
	{
		rules = init_rules(ac, av);
		if (!rules)
			return (write(2, "Error Malloc\n", 13) - 13);
		rules->start = get_time();
		forker(rules);
	}
	else
		write(2, "Error arguments!\n", 17);
	return (0);
}
