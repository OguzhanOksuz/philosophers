/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:34:03 by ooksuz            #+#    #+#             */
/*   Updated: 2023/07/14 02:21:33 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
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
	int				l_fork;
	int				r_fork;
	int				eat_count;
	int				last_eat;
	pthread_t		p_thread;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				p_count;
	int				death_t;
	int				eat_t;
	int				sleep_t;
	int				max_eat;
	int				eaten;
	int				mutex;
	int				start;
	int				is_dead;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	read;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}					t_rules;

int		ft_atoi(char *str);
t_rules	*init_rules(int ac, char **av);
int		rw_val(pthread_mutex_t *lock, int *data, int new_d);
void	*thread(void *ptr);
int		get_time(void);
void	my_free(t_rules *rules);
void	ft_print(int num, t_philo *philo);
void	u_sleep(int time);
void	*threads(void *ptr);
void	reaper(t_rules *rules);

#endif
