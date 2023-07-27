/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:38:16 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/27 15:21:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

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
	int				is_dead;
	pthread_t		death;
	struct s_rules	*rules;
	pthread_mutex_t	read;
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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
}					t_rules;

int		ft_atoi(char *str);
int		get_time(void);
void	my_free(t_rules *rules);
t_rules	*init_rules(int ac, char **av);
void	u_sleep(int time);
void	ft_print(int code, t_philo *philo);
void	routine(t_philo *philo);
void	end_program(t_rules *rules);

#endif
