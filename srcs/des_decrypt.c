/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:42:15 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/25 13:41:34 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		decrypt_cycle(t_subkey ks, int i)
{
	int			j;
	t_ubyte		temp;

	j = -1;
	while (++j < 6)
	{
		temp = ks[i][j];
		ks[i][j] = ks[17 - i][j];
		ks[17 - i][j] = temp;
	}
}

t_string	des_decrypt(t_ubyte *key, t_ubyte *message, int len)
{
	t_string	result;
	t_subkey	ks;
	int			i;
	t_ubyte		pad_byte;

	result = (t_string){0, 0};
	get_sub_keys(key, ks);
	i = 0;
	while (++i < 9)
		decrypt_cycle(ks, i);
	result.data = (t_ubyte *)ft_memalloc(len);
	ft_memcpy(result.data, message, len);
	result.len = len;
	i = 0;
	while (i < result.len)
	{
		process_message(&result.data[i], ks, &result.data[i]);
		i += 8;
	}
	pad_byte = result.data[len - 1];
	result.len -= pad_byte;
	return (result);
}
