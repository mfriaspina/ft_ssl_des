/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:41:10 by mfrias            #+#    #+#             */
/*   Updated: 2019/09/26 21:12:33 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	get_g(int i)
{
	if (i < 16)
		return (i);
	else if (i < 32)
		return ((5 * i + 1) % 16);
	else if (i < 48)
		return ((3 * i + 5) % 16);
	return ((7 * i) % 16);
}

uint32_t	get_f(uint32_t *val, int i)
{
	if (i < 16)
		return ((val[1] & val[2]) | ((~val[1]) & val[3]));
	else if (i < 32)
		return ((val[3] & val[1]) | ((~val[3]) & val[2]));
	else if (i < 48)
		return (val[1] ^ val[2] ^ val[3]);
	return (val[2] ^ (val[1] | (~val[3])));
}

void		get_val(uint32_t *o, uint32_t *val)
{
	val[0] = o[0];
	val[1] = o[1];
	val[2] = o[2];
	val[3] = o[3];
	val[4] = o[4];
	val[5] = o[5];
	val[6] = o[6];
	val[7] = o[7];
}

uint32_t	*get_w(uint32_t *msg, int i)
{
	uint32_t	*w;
	int			j;
	uint32_t	s[2];

	w = ft_memalloc(512);
	ft_memcpy(w, &msg[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		s[0] = (RIGHTROTATE(w[j - 15], 7)) ^ (RIGHTROTATE(w[j - 15], 18))
			^ (w[j - 15] >> 3);
		s[1] = (RIGHTROTATE(w[j - 2], 17)) ^ (RIGHTROTATE(w[j - 2], 19))
			^ (w[j - 2] >> 10);
		w[j] = w[j - 16] + s[0] + w[j - 7] + s[1];
		j++;
	}
	return (w);
}

uint32_t	sha_rev(uint32_t n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}
