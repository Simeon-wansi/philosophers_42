/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:36:44 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:01:45 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*[time_ms] [philo] [action]*/

#include "philosopher.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
        if (status ==  TAKE_RIGHT_FORK && !simulation_finished(philo->table))
            printf("%-6ld %d has taken a fork 1\t\t\t n:B[🍴 %d 🍴]", elapsed, philo->id, philo->r_fork->fork_id);
        if (status ==  TAKE_LEFT_FORK && !simulation_finished(philo->table))
            printf("%-6ld %d has taken a fork 2\n \t\t n:B[🍴 %d 🍴]", elapsed, philo->id, philo->l_fork->fork_id);
        else if (status == EATING && !simulation_finished(philo->table))
            printf("%-6ld %d is eating\t\t\t *%ld\n", elapsed, philo->id, philo->meal_counter);
        else if (status ==  SLEEPING && !simulation_finished(philo->table))
            printf("%-6ld %d is sleeping\n", elapsed , philo->id);
        else if (status ==  THINKING && !simulation_finished(philo->table))
            printf("%-6ld %d is THIKING\n", elapsed, philo->id);
        else if (status ==  DIED)
            printf("💀%-6ld %d died\n", elapsed, philo->id);
}
void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;
    
    elapsed =  gettime(MILISECOND) - philo->table->start_simulation;
    if (philo->full)
        return;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status ==  TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) && !simulation_finished(philo->table))
            printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
        else if (status == EATING && !simulation_finished(philo->table))
            printf("%-6ld %d is eating\n", elapsed, philo->id);
        else if (status ==  SLEEPING && !simulation_finished(philo->table))
            printf("%-6ld %d is sleeping\n", elapsed , philo->id);
        else if (status ==  THINKING && !simulation_finished(philo->table))
            printf("%-6ld %d is THIKING\n", elapsed, philo->id);
        else if (status ==  DIED)
            printf("%-6ld %d died\n", elapsed, philo->id);
    }
    
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}