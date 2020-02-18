/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:11:51 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/15 14:59:41 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_h_table[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372,
	0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

static const uint32_t	g_k_table[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void		print(uint32_t *h)
{
	int		i;

	i = -1;
	while (++i < 8)
		ft_printf("%08.8x", h[i]);
}

/*
** val[0] = a, val[1] = b, val[2] = c, val[3] = d
** val[4] = e, val[5] = f, val[6] = g, val[7] = h
*/

static void		loop(uint32_t *val, uint32_t *w, int i)
{
	uint32_t	s[2];
	uint32_t	ch;
	uint32_t	temp[2];
	uint32_t	maj;

	s[1] = (rightrotate(val[4], 6)) ^ (rightrotate(val[4], 11))
		^ (rightrotate(val[4], 25));
	ch = (val[4] & val[5]) ^ ((~val[4]) & val[6]);
	temp[0] = val[7] + s[1] + ch + g_k_table[i] + w[i];
	s[0] = (rightrotate(val[0], 2)) ^ (rightrotate(val[0], 13))
		^ (rightrotate(val[0], 22));
	maj = (val[0] & val[1]) ^ (val[0] & val[2]) ^ (val[1] & val[2]);
	temp[1] = s[0] + maj;
	val[7] = val[6];
	val[6] = val[5];
	val[5] = val[4];
	val[4] = val[3] + temp[0];
	val[3] = val[2];
	val[2] = val[1];
	val[1] = val[0];
	val[0] = temp[0] + temp[1];
}

static uint32_t	*each_offset(uint32_t *w, uint32_t *o)
{
	uint32_t	val[8];
	int			i;

	get_val(o, val);
	i = -1;
	while (++i < 64)
		loop(val, w, i);
	o[0] += val[0];
	o[1] += val[1];
	o[2] += val[2];
	o[3] += val[3];
	o[4] += val[4];
	o[5] += val[5];
	o[6] += val[6];
	o[7] += val[7];
	free(w);
	return (o);
}

static uint32_t	*padding(char *old_msg, size_t len, size_t *new_len)
{
	uint32_t	*msg;
	size_t		i;

	*new_len = 1 + (((len * 8) + 16 + 64) / 512);
	if (!(msg = malloc(16 * *new_len * 4)))
		return (NULL);
	ft_bzero(msg, 16 * *new_len * 4);
	ft_memcpy((char *)msg, old_msg, ft_strlen(old_msg));
	((char *)msg)[ft_strlen(old_msg)] = 0x80;
	i = 0;
	while (i < (*new_len * 16) - 1)
	{
		msg[i] = sha_rev(msg[i]);
		i++;
	}
	msg[((*new_len * 512 - 64) / 32) + 1] = len * 8;
	return (msg);
}

void			sha256(char *old_msg, size_t initial_len)
{
	uint32_t	*msg;
	size_t		offset;
	uint32_t	*h;
	size_t		new_len;

	if (!initial_len)
	{
		ft_putstr(
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
		return ;
	}
	msg = padding(old_msg, initial_len, &new_len);
	h = (uint32_t[8]) {g_h_table[0], g_h_table[1], g_h_table[2], g_h_table[3],
		g_h_table[4], g_h_table[5], g_h_table[6], g_h_table[7]};
	offset = 0;
	while (offset < new_len)
	{
		h = each_offset(get_w(msg, offset), h);
		offset++;
	}
	print(h);
	free(msg);
}
