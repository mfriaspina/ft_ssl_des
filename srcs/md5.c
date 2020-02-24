/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:31:50 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/23 17:11:45 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_h_table[] = {
	0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

static const uint32_t	g_s_table[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static const uint32_t	g_k_table[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
	0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static void				print(uint32_t *h)
{
	uint8_t			*p;
	int				i;

	i = -1;
	while (++i < 4)
	{
		p = (uint8_t *)&h[i];
		ft_printf("%02.2x%02.2x%02.2x%02.2x", p[0], p[1], p[2], p[3]);
	}
}

/*
**	val[0] = a, val[1] = b, val[2] = c, val[3] = d
**	val[4] = f
**	val[5] = g
*/

static uint32_t			*each_offset(uint32_t *w, uint32_t *o)
{
	uint32_t	val[6];
	int			i;
	uint32_t	temp;

	val[0] = o[0];
	val[1] = o[1];
	val[2] = o[2];
	val[3] = o[3];
	i = -1;
	while (++i < 64)
	{
		val[4] = get_f(val, i);
		val[5] = get_g(i);
		temp = val[3];
		val[4] = val[4] + val[0] + g_k_table[i] + w[val[5]];
		val[3] = val[2];
		val[2] = val[1];
		val[1] = val[1] + leftrotate(val[4], g_s_table[i]);
		val[0] = temp;
	}
	o[0] += val[0];
	o[1] += val[1];
	o[2] += val[2];
	o[3] += val[3];
	return (o);
}

static char				*padding(char *old_msg, size_t len, size_t *new_len)
{
	char		*message;

	*new_len = ((((len + 8) / 64) + 1) * 64) - 8;
	message = ft_strnew(*new_len + 64);
	ft_bzero(message, *new_len + 64);
	ft_strcpy(message, old_msg);
	message[len] = (char)0x80;
	*(uint32_t*)(message + *new_len) = (uint32_t)(8 * len);
	return (message);
}

void					md5(char *old_msg, size_t initial_len)
{
	char		*msg;
	size_t		offset;
	uint32_t	*h;
	size_t		new_len;

	if (!initial_len)
	{
		ft_putstr("d41d8cd98f00b204e9800998ecf8427e");
		return ;
	}
	msg = padding(old_msg, initial_len, &new_len);
	offset = 0;
	h = (uint32_t[4]) {g_h_table[0], g_h_table[1], g_h_table[2], g_h_table[3]};
	while (offset < new_len)
	{
		h = each_offset((uint32_t *)(msg + offset), h);
		offset += 64;
	}
	print(h);
	ft_strdel(&msg);
}

char					*execute_md5(char *old_msg, size_t initial_len,
						size_t offset, size_t new_len)
{
	char		*msg;
	uint32_t	*h;
	char		*temp;
	char		*o;

	o = ft_strnew(32);
	msg = padding(old_msg, initial_len, &new_len);
	h = (uint32_t[4]) {g_h_table[0], g_h_table[1], g_h_table[2], g_h_table[3]};
	while (offset < new_len)
	{
		h = each_offset((uint32_t *)(msg + offset), h);
		offset += 64;
	}
	new_len = 0;
	while (new_len < 16)
	{
		temp = ft_itoa_base(((uint8_t *)&h[new_len / 4])[new_len % 4], 16);
		while (ft_strlen(temp) < 2)
			temp = free_strjoin("0", temp, 1);
		o = ft_strcat(o, temp);
		ft_strdel(&temp);
		new_len++;
	}
	ft_strdel(&msg);
	return (o);
}
