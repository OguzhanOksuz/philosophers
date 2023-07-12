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
	int				is_dead;
	int				eaten;
	int				mutex;
	int				start;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	read;
}					t_rules;

int		ft_atoi(char *str);
t_philo	**philos_error_free(t_philo **philo, int i);
t_rules	*init_rules(int ac, char **av);
int		rw_val(pthread_mutex_t *lock, int *data, int new_d);
void	*thread(void *ptr);
int		get_time(void);
void	free_rules(t_rules *rules);
void	free_philos(t_philo **philos);
void	ft_print(int num, t_philo *philo);
void	u_sleep(int time);
void	*threads(void *ptr);

#endif
