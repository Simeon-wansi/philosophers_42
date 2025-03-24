/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:34:04 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:03:32 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// int	ft_is_num(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!(str[i] >= '0' && str[i] <= '9'))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	is_valid_input(int ac, char **av)
// {
// 	int	i;

// 	if (!(ac == 4 || ac == 5))
// 		return (0);
// 	i = 0;
// 	while (i < ac)
// 	{
// 		if (!ft_is_num(av[i]) || ft_atoi(av[i] <= 0))
// 			return (0);
// 		i++;
// 	}
// 	if (ft_atoi(av[3]) > 200)
// 		return (0);
// 	return (1);
// }

/* The  main is the start of the program
example ./philo 7 800 200 200 [6] */

int	main(int ac, char **av)
{
    t_table table;

	if (ac == 5 || ac == 6)
	{ 
        /*cehecking error of input*/
        parse_input(&table, av);

        // /*creating data*/
        data_init(&table);

        // /* starting the dinner*/
        dinner_start(&table);

        // /*No leaks , when philo is dead or all philos are full*/
        // clean(&table);
	}
	else
	{
		error_exit("Wrong input \n"
				"Do ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
	}

	// if (!is_valid_input(ac - 1, av + 1))
	// {
	// 	write(1, "Error\n", 6);
	// 	return (1);
	// }
	// write(1, "Correct values\n", 15);
	return (0);
}