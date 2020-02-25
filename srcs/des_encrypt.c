/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:40:24 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/24 13:31:26 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const static t_ubyte g_ip[] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46,
	38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17,
	9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55,
	47, 39, 31, 23, 15, 7};

const static t_ubyte g_ip2[] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46,
	14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20,
	60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33,
	1, 41, 9, 49, 17, 57, 25};

void		message_cycle(t_des_algo *des, int i, t_subkey ks)
{
	t_ubyte fs[4];
	int		j;

	ft_memcpy(des->left[i], des->right[i - 1], 4);
	f(des->right[i - 1], ks[i], fs);
	j = -1;
	while (++j < 4)
		des->left[i - 1][j] ^= fs[j];
	ft_memcpy(des->right[i], des->left[i - 1], 4);
}

void		process_message(const t_ubyte *message, t_subkey ks, t_ubyte *ep)
{
	t_des_algo	des;
	int			i;

	i = -1;
	while (++i < 64)
		poke_bit(des.mp, i, peek_bit(message, g_ip[i] - 1));
	i = -1;
	while (++i < 32)
	{
		poke_bit(des.left[0], i, peek_bit(des.mp, i));
		poke_bit(des.right[0], i, peek_bit(des.mp, i + 32));
	}
	i = 0;
	while (++i < 17)
		message_cycle(&des, i, ks);
	i = -1;
	while (++i < 32)
		poke_bit(des.e, i, peek_bit(des.right[16], i));
	i = 31;
	while (++i < 64)
		poke_bit(des.e, i, peek_bit(des.left[16], i - 32));
	i = -1;
	while (++i < 64)
		poke_bit(ep, i, peek_bit(des.e, g_ip2[i] - 1));
}

t_string	des_encrypt(t_ubyte *key, t_ubyte *message, int len)
{
	t_string	result;
	t_subkey	ks;
	t_ubyte		pad_byte;
	int			i;

	result = (t_string){0, 0};
	get_sub_keys(key, ks);
	pad_byte = 8 - len % 8;
	result.len = len + pad_byte;
	result.data = (t_ubyte *)ft_memalloc(result.len);
	ft_memcpy(result.data, message, len);
	ft_memset(&result.data[len], pad_byte, pad_byte);
	i = 0;
	while (i < result.len)
	{
		process_message(&result.data[i], ks, &result.data[i]);
		i += 8;
	}
	return (result);
}
