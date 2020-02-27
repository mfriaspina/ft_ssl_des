/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64code.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:13:34 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/26 13:37:45 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char	g_b64_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'm', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'};

void		octet_to_sextet(char *data, size_t *i, size_t len, char *out)
{
	uint32_t	octet[3];
	uint32_t	triple;
	size_t		out_len;

	octet[0] = *i < len ? (unsigned char)data[(*i)++] : 0;
	octet[1] = *i < len ? (unsigned char)data[(*i)++] : 0;
	octet[2] = *i < len ? (unsigned char)data[(*i)++] : 0;
	triple = (octet[0] << 0x10) + (octet[1] << 0x08) + octet[2];
	out_len = ft_strlen(out);
	out[out_len++] = g_b64_table[(triple >> 3 * 6) & 0x3F];
	out[out_len++] = g_b64_table[(triple >> 2 * 6) & 0x3F];
	out[out_len++] = g_b64_table[(triple >> 1 * 6) & 0x3F];
	out[out_len++] = g_b64_table[(triple >> 0 * 6) & 0x3F];
	out[out_len] = '\0';
}

char		*encode(char *line, size_t in_len)
{
	char	*out;
	size_t	i;

	out = ft_strnew(4 * ((in_len) / 3));
	i = 0;
	while (i < in_len)
		octet_to_sextet(line, &i, in_len, out);
	if (in_len % 3 == 1)
	{
		out[ft_strlen(out) - 1] = '=';
		out[ft_strlen(out) - 2] = '=';
	}
	else if (in_len % 3 == 2)
		out[ft_strlen(out) - 1] = '=';
	return (out);
}

static int	*get_decrypt_table(char *input, size_t in_len, size_t *o_len)
{
	static int	table[256];
	char		*t;
	int			count;

	t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	count = -1;
	while (++count < 64)
		table[(int)t[count]] = count;
	*o_len = 3 * (in_len / 4);
	*o_len -= input[in_len - 1] == '=' ? 1 : 0;
	*o_len -= input[in_len - 2] == '=' ? 1 : 0;
	return (table);
}

char		*decode(char *input, size_t in_len)
{
	t_base64	b;
	char		*output;
	int			*t;
	size_t		o_len;

	if (!(t = get_decrypt_table(input, in_len, &o_len)))
		return (NULL);
	if (!(output = ft_strnew(o_len)))
		return (NULL);
	b.i = 0;
	b.j = -1;
	while (b.i < in_len && (b.k = -1))
	{
		b.res_a = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_b = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_c = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_d = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_e = (b.res_a << 18) + (b.res_b << 12) + (b.res_c << 6) + b.res_d;
		while (++b.k < 3 && ++b.j < o_len)
			output[b.j] = (char)((b.res_e >> (16 - (8 * b.k))) & 0xFF);
	}
	return (output);
}
