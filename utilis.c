/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:33:34 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 17:35:05 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"


/* gettimeofday*/

long gettime(t_time_code time_code)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if(time_code ==  MILISECOND)
		return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (1337);
}

/* Presice Usleep*/
//1) Usleep the majority of time ,not CPU intensive 
//2) refine last microsec with spinlock
void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECOND);
	while(gettime(MICROSECOND) - start < usec)
	{
		//1
		if (simulation_finished(table))
			break;
		elapsed =  gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		// to gte a spinlock thresh
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			//Spinlock
			while (gettime(MICROSECOND) - start < usec);			
		}
	}
}
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}


void error_exit(const char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

