/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:46:20 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/17 12:14:49 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	to_hex(t_ubyte in)
{
	if (0x00 <= in && in < 0x0A)
		return ('0' + in);
	if (0x0A <= in && in <= 0x0F)
		return ('A' + in - 0x0A);
	return (0);
}

void	print_bytes(t_ubyte *ptr, int len, char *out)
{
	while (len-- > 0)
	{
		*out++ = to_hex(*ptr >> 4);
		*out++ = to_hex(*ptr & 0x0F);
		ptr++;
	}
	*out = 0;
}

int		peek_bit(const t_ubyte *src, int index)
{
	int cell;
	int bit;

	cell = index / 8;
	bit = 7 - index % 8;
	return ((src[cell] & (1 << bit)) != 0);
}

void	poke_bit(t_ubyte *dst, int index, int value)
{
	int cell;
	int bit;

	cell = index / 8;
	bit = 7 - index % 8;
	if (value == 0)
		dst[cell] &= ~(1 << bit);
	else
		dst[cell] |= (1 << bit);
}

void	shift_left(const t_ubyte *src, int len, int times, t_ubyte *dst)
{
	int i;
	int t;
	int	temp;

	i = -1;
	while (++i < len)
		poke_bit(dst, i, peek_bit(src, i));
	t = 0;
	while (++t <= times)
	{
		temp = peek_bit(dst, 0);
		i = 0;
		while (++i <= len)
			poke_bit(dst, i - 1, peek_bit(dst, i));
		poke_bit(dst, len - 1, temp);
	}
}
