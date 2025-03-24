/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:35:15 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/22 18:29:56 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

/* Module containing getter and setter functions
t avoid writing LOCK AND UNLOCK everywhere
*/

//bool
void set_bool(t_mutex *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mutex *mutex, bool *value)
{
    bool res;

    safe_mutex_handle(mutex, LOCK);
    // reading thread safe
    res = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (res);
}


void set_long(t_mutex *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

/* it's redundant*/

bool simulation_finished(t_table *table)
{
    return(get_bool(&table->table_mutex, &table->end_simlation));
}