/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:31:09 by abollen           #+#    #+#             */
/*   Updated: 2022/03/01 20:41:50 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	protmalloc(int code, t_pdata *pdata)
{
	if (code == 1)
		return (1);
	else if (code == 2)
	{
		free(pdata->philo);
		return (1);
	}
	else if (code == 3)
	{
		free(pdata->philo);
		free(pdata->ph);
		return (1);
	}
	return (0);
}

int	protthread(int index, t_pdata *pdata)
{
	int	i;

	if (index == -1)
	{
		return (1);
	}
	else if (index > 0)
	{
		pdata->run = -1;
		if (pthread_join(pdata->bigbrother, NULL) != 0)
			return (1);
		i = -1;
		while (++i < index)
		{
			pthread_join(pdata->philo[i], NULL);
			pthread_mutex_destroy(&pdata->forks[i]);
			pthread_mutex_destroy(&pdata->ph[i].datalock);
		}
		pthread_mutex_destroy(&pdata->ph[index].datalock);
		mallocdestroy(pdata);
	}
	return (0);
}
