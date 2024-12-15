/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:00:52 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:42:40 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mallocdestroy(t_pdata *pdata)
{
	while (pdata->run)
		;
	free(pdata->philo);
	free(pdata->ph);
	free(pdata->forks);
}

int	threaddestroy(t_pdata *pdata)
{
	int	i;

	pthread_join(pdata->bigbrother, NULL);
	i = -1;
	while (++i < pdata->philo_count)
		pthread_join(pdata->philo[i], NULL);
	i = -1;
	while (++i < pdata->philo_count)
	{
		pthread_mutex_destroy(&pdata->forks[i]);
		pthread_mutex_destroy(&pdata->ph[i].datalock);
	}
	pthread_mutex_destroy(&pdata->mic);
	pthread_mutex_destroy(&pdata->simlock);
	return (0);
}
