/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:13:42 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/28 16:55:06 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_cbc(t_des *des, t_ubyte *str)
{
	t_ubyte	*temp;
	int		i;

	if (des->mode)
	{
		temp = (t_ubyte *)ft_memalloc(sizeof(t_ubyte) * 9);
		i = -1;
		while (++i < 8)
			temp[i] = str[i] ^ des->iv[i];
		ft_memcpy(str, temp, 8);
		free(temp);
	}
}

void	process_cbc_dec(t_des *des, t_ubyte *str)
{
	t_ubyte	*temp;
	int		i;

	if (des->mode)
	{
		temp = (t_ubyte *)ft_memalloc(sizeof(t_ubyte) * 9);
		i = -1;
		while (++i < 8)
			temp[i] = str[i] ^ des->iv[i];
		ft_memcpy(str, temp, 8);
		free(temp);
		ft_memcpy(des->iv, des->temp, 8);
		free(des->temp);
	}
}

void	cbc_dec(t_des *des, t_ubyte *str)
{
	if (des->mode)
	{
		des->temp = (t_ubyte *)ft_memalloc(sizeof(t_ubyte) * 8);
		ft_memcpy(des->temp, str, 8);
	}
}
