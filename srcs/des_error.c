/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:14:36 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/21 12:09:57 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_hex(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] >= 'a' && str[j] <= 'f')
			i = 1;
		if (str[j] >= 'A' && str[j] <= 'F')
			i = 1;
		if (str[j] != 0 && !ft_isdigit(str[j]) && !i)
			return (0);
		j++;
	}
	return (1);
}

void	free_exit(char *str, void *to_free)
{
	ft_putstr(str);
	if (to_free)
		free(to_free);
	exit(EXIT_FAILURE);
}
