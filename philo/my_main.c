/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:33:38 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/02 15:31:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	is_in_range(char *str)
{
	int				i;
	long long int	num;

	i = 0;
	num = 0;
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	if (num > 0 && num <= 2147483647)
		return (1);
	else
		return (0);
}

int	is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
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

int	main(int ac, char **av)
{
	t_rules	*rules;
	int		i;

	if (is_av_valid(ac, av))
	{
		rules = init_rules(ac, av);
		if (!rules)
			return (write(2, "Error Malloc\n", 13) - 13);
		i = -1;
		while (++i < rules->p_count)
			pthread_create(&rules->philos[i]->p_thread,
				NULL, threads, (void *)rules->philos[i]);
		reaper(rules);
		my_free(rules);
		free(rules->philos);
		free(rules);
	}
	else
		write(2, "Error arguments!\n", 17);
	return (0);
}
