/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:39:12 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:15:45 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int is_space(char c)
{
    return (c == ' ' || c == '\t' ||c == '\n'
			|| c == '\r' || c == '\v' || c == '\f');
}

int	is_digit(int c)
{
	return ((c >= '0' && c <= '9'));
}
static char *valid_input(const char *str)
{
    int len;
    const char *num_str;
    
    len = 0;
    while(is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        error_exit("Error: Only positive numbers are allowed\n");
    if(!is_digit(*str))
        error_exit("Error: Only Number are allowed\n");
    num_str = str;
    while (is_digit(*str++))
        len++;
    if (len > 10)
        error_exit("The value is too big , INT_MAX is the limit\n");
    return ((char *)num_str);
    
}

static long	ft_atol(const char *str)
{
	long	num;
	int		i;

	num = 0;
    str  =  valid_input(str);
	i = 0;
	while(is_digit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		error_exit("The value is too big , INT_MAX is the limit\n");
	return (num );
}

/* Parsing the input*/
void parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]); // we mutipliy by 1e3 because we want in ms not in seconds
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4) // 6e4 here represent 6 seconds
		error_exit("Error: time_to_die , time_to_eat and time_to_sleep must be greater than 6 seconds\n");
	if (av[5])
		table->nbr_limit_meal = ft_atol(av[5]);
	else
		table->nbr_limit_meal = -1;
	// printf("Number of philosophers: %ld\n", table->philo_nbr);
	// printf("Time to die: %ld ms\n", table->time_to_die);
	// printf("Time to eat: %ld ms\n", table->time_to_eat);
	// printf("Time to sleep: %ld ms\n", table->time_to_sleep);
	// printf("Number of times each philosopher must eat: %ld\n", table->nbr_limit_meal);
	
}
