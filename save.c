/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:29:06 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:08:48 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


/*Module containing wrapper functions with embeded controls on return*/

void *save_malloc(size_t bytes)
{
    void *res;

    res =  malloc(bytes);
    if (!res)
        error_exit("Malloc failed");
    return (res);
}

/* MEbed controls on return status*/

static void handle_mutex_error(int status, t_opcode opcode)
{
    if (status == 0)
        return;
    if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by the mutex attribute is invalid");
    else if (status == EDEADLK)
        error_exit("A dreadock will occur if the thread locked waiting for mutex.");
    else if (status ==  EPERM)
        error_exit("The current thread does not hold a lock on mutex");
    else if (status == ENOMEM)
        error_exit("The process can' allocate enough memory");
    else if (status == EBUSY)
        error_exit("The mutex is already in lock");
    else
        error_exit("Unknown error");
}

/* Mutex save */
/* init
    destroy
    lock
    unlock
*/

void safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        handle_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        handle_mutex_error( pthread_mutex_unlock(mutex), opcode);
    else if (opcode == INIT)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (opcode == DESTROY)
        handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("Invalid opcode to handle mutex");
} 

// *pthread part

/* MEbed controls on return status*/

static void handle_thread_error(int status, t_opcode opcode)
{
    if (status == 0)
        return;
    if (status == EAGAIN)
        error_exit("No ressource to create another thread\n");
    else if (status == EPERM)
        error_exit("The caller doesnt have appropriate permissions\n");
    else if (status == EINVAL && opcode == CREATE)
        error_exit("The value specified by the thread attribute is invalid\n");
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit("The valeu specified by the thread is not joinable ");
    else if (status == ESRCH)
        error_exit("The specified thread does not exist\n");
    else if (status == EDEADLK)
        error_exit("A deadlock was detected or the value of 'Thread specifies the calling thread\n");
    else
        error_exit("Unknown error");
}

/* Thread save*/

void safe_thread_handle(pthread_t *thread, void*(*foo)(void *), void *data, t_opcode opcode)
{
    if (opcode == CREATE)
        handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);    
    else if (opcode == JOIN )
        handle_thread_error(pthread_join(*thread, NULL), opcode);
    else if (opcode == DETACH)
        handle_thread_error(pthread_detach(*thread), opcode);
    else
        error_exit("Invalid opcode to handle thread: use <CREATE> <JOIN> or <DETACH>");
} 