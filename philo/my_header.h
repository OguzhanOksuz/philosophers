#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

int		ft_atio(char *str);
t_rules	*init_rules(int ac, char **av);
void	philo(t_rules *rules);

typedef struct	s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long long		last_eat;
	pthread_t	p_thread;
	struct s_rules		*rules;
}				t_philo;

typedef struct s_rules
{
	int			p_count;
	int			death_t;
	int			eat_t;
	int			sleep_t;
	int			max_eat;
	int			is_dead;
	int			eaten;
	int			mutex;
	long long	start;
	t_philo		**philos;
	pthread_mutex_t	*forks;
}			t_rules;

#endif
