/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:14:36 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/24 12:59:30 by mfrias           ###   ########.fr       */
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

void	check_free(t_des *des)
{
	if (des->key)
		free(des->key);
	if (des->salt)
		free(des->salt);
	if (des->iv)
		free(des->iv);
	if (des->str)
		free(des->str);
	free(des);
}

void	free_exit(char *str, t_des *des)
{
	if (str)
		ft_putstr(str);
	if (des)
		check_free(des);
	exit(EXIT_FAILURE);
}
