/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:27:21 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:02:17 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static void assign_fork(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;
    
    philo_nbr = philo->table->philo_nbr;
    
    //==to position
    philo->r_fork = &forks[(philo_position + 1) % philo_nbr];
    philo->l_fork = &forks[philo_position];
    if (philo->id % 2 == 0)
    {
        philo->r_fork = &forks[philo_position];
        philo->l_fork = &forks[(philo_position + 1) % philo_nbr];
    }    
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        philo->table = table;
        safe_mutex_handle(&philo->philo_mutex, INIT);
        //function to asign forks to philo / i position in the table
        assign_fork(philo, table->forks, i);
    }
}
void	data_init( t_table *table)
{
    int i;

    i = -1;
    table->end_simlation = false;
    table->all_threads_ready =  false;
    table->philos = save_malloc(sizeof(t_philo) * table->philo_nbr);
    safe_mutex_handle(&table->table_mutex, INIT);
    safe_mutex_handle(&table->write_mutex, INIT);
    table->forks = save_malloc(sizeof(t_fork) * table->philo_nbr);
    while( ++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}