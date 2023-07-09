#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <unistd.h>
# include <stdlib.h>

int		ft_atio(char *str);
void	philo(int ac, char **av);

typedef struct	s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long long		last_eat;
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
	int			mutux
	long long	start;
	t_phlo		**philos;
	pthread_mutex_t	*forks;
}			t_rules;

#endif
