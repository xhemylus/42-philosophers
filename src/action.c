/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:38:29 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:56:06 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosleep(int id, t_philosophers *ph)
{
	pthread_mutex_lock(&ph->sys->mic);
	pthread_mutex_lock(&ph->sys->simlock);
	if (ph->sys->run)
		printf("%llu %d is sleeping\n", ms_time(ph->sys), id);
	pthread_mutex_unlock(&ph->sys->simlock);
	pthread_mutex_unlock(&ph->sys->mic);
	milisleep(ph->sys->time_to_sleep, ph->sys);
}

void	philofork(int id, t_philosophers *ph)
{
	pthread_mutex_lock(&ph->sys->mic);
	pthread_mutex_lock(&ph->sys->simlock);
	if (ph->sys->run)
		printf("%llu %d has taken a fork\n", ms_time(ph->sys), id);
	pthread_mutex_unlock(&ph->sys->simlock);
	pthread_mutex_unlock(&ph->sys->mic);
}

void	philoeat(int id, t_philosophers *ph)
{
	pthread_mutex_lock(&ph->sys->mic);
	pthread_mutex_lock(&ph->sys->simlock);
	if (ph->sys->run)
		printf("%llu %d is eating\n", ms_time(ph->sys), id);
	pthread_mutex_unlock(&ph->sys->simlock);
	pthread_mutex_unlock(&ph->sys->mic);
}

void	philothink(int id, t_philosophers *ph)
{
	pthread_mutex_lock(&ph->sys->mic);
	pthread_mutex_lock(&ph->sys->simlock);
	if (ph->sys->run)
		printf("%llu %d is thinking\n", ms_time(ph->sys), id);
	pthread_mutex_unlock(&ph->sys->simlock);
	pthread_mutex_unlock(&ph->sys->mic);
}

void	philodie(int id, t_pdata *pdata)
{
	pthread_mutex_lock(&pdata->simlock);
	pdata->run = 0;
	pthread_mutex_unlock(&pdata->simlock);
	pthread_mutex_lock(&pdata->mic);
	printf("%llu %d died\n", ms_time(pdata), id);
	pthread_mutex_unlock(&pdata->mic);
}
