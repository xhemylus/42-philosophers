/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:00:13 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:43:55 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mallocinit(t_pdata *pdata)
{
	pdata->philo = malloc(sizeof(pthread_t) * pdata->philo_count);
	if (!pdata->philo)
		return (1);
	pdata->ph = malloc(sizeof(t_philosophers) * pdata->philo_count);
	if (!pdata->ph)
		return (2);
	pdata->forks = malloc(sizeof(pthread_mutex_t) * pdata->philo_count);
	if (!pdata->forks)
		return (3);
	return (0);
}

int	threadinit(t_pdata *pdata)
{
	int	i;

	if (pthread_create(&pdata->bigbrother, NULL, &bigbrother, pdata) != 0)
		return (-1);
	i = -1;
	while (++i < pdata->philo_count)
	{
		pthread_mutex_init(&pdata->ph[i].datalock, NULL);
		pdata->ph[i].id = i + 1;
		pthread_mutex_lock(&pdata->ph[i].datalock);
		pdata->ph[i].meal_count = 0;
		pdata->ph[i].timeofmeal = 0;
		pthread_mutex_unlock(&pdata->ph[i].datalock);
		pdata->ph[i].rfork = &pdata->forks[i];
		pdata->ph[i].lfork = &pdata->forks[(i + 1) % pdata->philo_count];
		pdata->ph[i].sys = pdata;
		if (pthread_create(&pdata->philo[i], NULL, &philo, &pdata->ph[i]) != 0)
			return (i);
		pthread_mutex_init(&pdata->forks[i], NULL);
	}
	pthread_mutex_init(&pdata->mic, NULL);
	pthread_mutex_init(&pdata->simlock, NULL);
	return (0);
}
