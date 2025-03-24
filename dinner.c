/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:12:39 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 20:59:08 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

# define DEBUG_MODE 0


static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

/*
*Eat routine 
* 1) grap the fork: here the right & left fork is handy
* i dont worry about left 
* 2) eat: write eat , update last meal, update meal counter
* 3) release the forks

*/

static void eat(t_philo *philo)
{
    //1
    safe_mutex_handle(&philo->r_fork->fork, LOCK);
    write_status(TAKE_RIGHT_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->l_fork->fork, LOCK);
    write_status(TAKE_LEFT_FORK, philo, DEBUG_MODE);

    //2
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
    philo->meal_counter++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_limit_meal > 0 && philo->meal_counter == philo->table->nbr_limit_meal)
      set_bool(&philo->philo_mutex, &philo->full, true);

    //3
    safe_mutex_handle(&philo->r_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->l_fork->fork, UNLOCK);
}

void *dinner_simulation(void *data)
{
    t_philo *philo;
    
    philo  = (t_philo *)data;
    //spinlock
    wait_all_threads(philo->table);
    
    // Set last meal time
    while(!simulation_finished(philo->table))
    {
        // 1) philo check , am I full
        if (philo->full) // to do
            break;

        // 2) eat
        eat(philo);
        
        // 3 sleep -> write_status & precide usleep
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);

        // 4) thinking
        thinking(philo);
    } 
    return (NULL);
}


/* @ the meat
./philo 7 200 200 200 [5]

0) if no meal return [0]
0.1) if only one philo  ad hoc funct
1) create all threads, all philo
2) Create a monitor thread 
3) Synchronize  the begining of the simulation
  pthread_create-> philo start running!
  every philo start simultaneously 
4) Join all  
*/


void dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->nbr_limit_meal == 0)
        return ;
    else if (table->philo_nbr == 1)
        ;//Todo
    else
    {
        while(++i < table->philo_nbr)
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
    }

    // start of simulation
    table->start_simulation =  gettime(MILISECOND);
    
    // Now all threads are ready to start
    set_bool(&table->table_mutex, &table->all_threads_ready, true);

    // Wait for all threads to finish
    i = -1;
    while(++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);  
}