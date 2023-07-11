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
