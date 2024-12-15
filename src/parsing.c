/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:04:13 by abollen           #+#    #+#             */
/*   Updated: 2022/02/25 14:20:47 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	posatoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res *= 10;
		res += str[i] - '0';
		if (res < INT_MIN || res > INT_MAX)
			return (-1);
		i++;
	}
	return (res);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	check_int(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isdigit(argv[i]))
			return (0);
	}
	return (1);
}

int	parsing(int argc, char **argv, t_pdata *pdata)
{
	if (argc < 5 || !check_int(argc, argv) || argc > 6)
		return (1);
	pdata->total_meal = -2;
	pdata->philo_count = posatoi(argv[1]);
	pdata->time_to_die = posatoi(argv[2]);
	pdata->time_to_eat = posatoi(argv[3]);
	pdata->time_to_sleep = posatoi(argv[4]);
	if (argv[5])
		pdata->total_meal = posatoi(argv[5]);
	if (pdata->philo_count == -1 || pdata->time_to_die == -1
		|| pdata->time_to_eat == -1 || pdata->time_to_sleep == -1
		|| pdata->total_meal == -1)
		return (1);
	return (0);
}
