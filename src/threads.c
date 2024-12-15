/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:49:14 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 21:08:28 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	syncstart(t_pdata *pdata)
{
	int	temprun;

	temprun = 0;
	while (!temprun)
	{
		usleep(50);
		pthread_mutex_lock(&pdata->simlock);
		temprun = pdata->run;
		pthread_mutex_unlock(&pdata->simlock);
	}
	return (temprun);
}

void	*philo(void *pdata)
{
	t_philosophers	*ph;
	int				tempmcount;
	int				temprun;

	ph = (t_philosophers *)pdata;
	temprun = syncstart(ph->sys);
	tempmcount = 0;
	while (temprun && tempmcount < ph->sys->total_meal)
	{
		philothink(ph->id, ph);
		if (ph->id % 2 == 1 && ph->meal_count == 0)
			usleep(500);
		eat(ph->id, ph);
		philosleep(ph->id, ph);
		philothink(ph->id, ph);
		pthread_mutex_lock(&ph->datalock);
		tempmcount = ph->meal_count;
		pthread_mutex_unlock(&ph->datalock);
		pthread_mutex_lock(&ph->sys->simlock);
		temprun = ph->sys->run;
		pthread_mutex_unlock(&ph->sys->simlock);
	}
	return (NULL);
}

void	checkfull(t_pdata *pdata)
{
	if (pdata->isfull)
	{
		pthread_mutex_lock(&pdata->simlock);
		pdata->run = 0;
		pthread_mutex_unlock(&pdata->simlock);
	}
}

void	*bigbrother(void *data)
{
	t_pdata		*pdata;
	int			i;

	pdata = (t_pdata *)data;
	while (!pdata->run)
		;
	while (pdata->run)
	{
		i = -1;
		pdata->isfull = 1;
		while (++i < pdata->philo_count && pdata->run)
		{
			pthread_mutex_lock(&pdata->ph[i].datalock);
			pdata->tom = pdata->ph[i].timeofmeal;
			pdata->solofull = pdata->ph[i].meal_count >= pdata->total_meal;
			pdata->solofull = (pdata->solofull && (pdata->total_meal != -2));
			pthread_mutex_unlock(&pdata->ph[i].datalock);
			if (ms_time(pdata) - pdata->tom >= (u_int64_t)pdata->time_to_die)
				philodie(i + 1, pdata);
			pdata->isfull = (pdata->isfull && pdata->solofull);
		}
		checkfull(pdata);
	}
	return (NULL);
}
