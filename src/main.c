/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:33:39 by abollen           #+#    #+#             */
/*   Updated: 2022/02/25 14:21:25 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_pdata		pdata;

	pdata.run = 0;
	if (parsing(argc, argv, &pdata))
		return (fterr("Error: Invalid Arguments.\n"));
	if (protmalloc(mallocinit(&pdata), &pdata))
		return (fterr("Error: Malloc Error.\n"));
	if (protthread(threadinit(&pdata), &pdata))
		return (fterr("Error: Thread Error.\n"));
	gettimeofday(&pdata.time.lau, NULL);
	pdata.run = 1;
	if (threaddestroy(&pdata) != 0)
		return (fterr("Error: Thread Error.\n"));
	mallocdestroy(&pdata);
	return (0);
}
