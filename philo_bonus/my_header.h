/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:38:16 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/15 00:47:26 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_philo
{
	int				id;
	int				pid;
	int				eat_count;
	int				last_eat;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				p_count;
	int				death_t;
	int				eat_t;
	int				sleep_t;
	int				max_eat;
	int				start;
	t_philo			**philos;
}					t_rules;

int		ft_atoi(char *str);
int		get_time(void);
t_rules	*init_rules(int ac, char **av);

#endif
