/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:14:36 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/20 12:50:55 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		is_hex(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= 'a' && str[0] <= 'f')
		i = 1;
	if (str[0] >= 'A' && str[0] <= 'F')
		i = 1;
	if (str[1] >= 'a' && str[1] <= 'f')
		i = 1;
	if (str[1] >= 'A' && str[1] <= 'F')
		i = 1;
	if (str[0] != 0 && !ft_isdigit(str[0]) && !i)
		return (0);
	if (str[1] != 0 && !ft_isdigit(str[1]) && !i)
		return (0);
	return (1);
}

void	free_exit(char *str, void *to_free)
{
	ft_putstr(str);
	if (to_free)
		free(to_free);
	exit(EXIT_FAILURE);
}
