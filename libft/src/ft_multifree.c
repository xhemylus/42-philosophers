/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multifree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:22:54 by abollen           #+#    #+#             */
/*   Updated: 2022/01/20 16:45:23 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_multifree(int count, ...)
{
	va_list	args;
	int		i;

	va_start(args, count);
	i = -1;
	while (++i < count)
		free(va_arg(args, char *));
	va_end(args);
	return (NULL);
}
