/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:34:23 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:54:01 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(int id, t_philosophers *ph)
{
	pthread_mutex_lock(ph->lfork);
	philofork(id, ph);
	if (ph->sys->philo_count != 1)
	{
		pthread_mutex_lock(ph->rfork);
		philofork(id, ph);
		philoeat(id, ph);
		milisleep(ph->sys->time_to_eat, ph->sys);
		pthread_mutex_lock(&ph->datalock);
		ph->meal_count++;
		ph->timeofmeal = ms_time(ph->sys);
		pthread_mutex_unlock(&ph->datalock);
		pthread_mutex_unlock(ph->rfork);
		pthread_mutex_unlock(ph->lfork);
	}
	else
	{
		pthread_mutex_unlock(ph->lfork);
		while (ph->sys->run)
			;
	}
}

u_int64_t	ms_time(t_pdata *pdata)
{
	u_int64_t		curtime;
	u_int64_t		time;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	curtime = (cur.tv_sec * (u_int64_t)1000)
		+ (cur.tv_usec / (u_int64_t)1000);
	time = curtime - ((pdata->time.lau.tv_sec * (u_int64_t)1000)
			+ (pdata->time.lau.tv_usec / (u_int64_t)1000));
	return (time);
}

int	fterr(char *str)
{
	printf("%s", str);
	return (1);
}

void	milisleep(u_int64_t time, t_pdata *pdata)
{
	int			temprun;
	u_int64_t	cur;

	cur = ms_time(pdata);
	temprun = 1;
	while (ms_time(pdata) - cur < time && temprun)
	{
		usleep(50);
		pthread_mutex_lock(&pdata->simlock);
		temprun = pdata->run;
		pthread_mutex_unlock(&pdata->simlock);
	}
}
