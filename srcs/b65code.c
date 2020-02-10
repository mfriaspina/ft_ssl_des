/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b65code.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:13:34 by mfrias            #+#    #+#             */
/*   Updated: 2019/12/14 14:14:18 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char	g_b64_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'm', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'};

static const int g_b64_d[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 63, 62, 62, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 0, 0, 0, 0, 63, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

void	octet_to_sextet(char *data, size_t *i, size_t len, char *out)
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

void	sextet_to_octet(char *p, size_t *i, char *out)
{
	int	n;
	int	j;

	n = g_b64_d[(int)p[*i]] << 18 | g_b64_d[(int)p[*i + 1]] << 12 |
		g_b64_d[(int)p[*i + 2]] << 6 | g_b64_d[(int)p[*i + 3]];
	j = ft_strlen(out);
	out[j++] = n >> 16;
	out[j++] = n >> 8 & 0xFF;
	out[j++] = n & 0xFF;
	out[j] = '\0';
	*i += 4;
}

char	*encode(char *line, size_t in_len)
{
	char	*out;
	size_t	i;

	out = ft_strnew(4 * ((in_len + 2) / 3));
	i = 0;
	while (i < in_len)
		octet_to_sextet(line, &i, in_len, out);
	if ((4 * ((in_len + 2) / 3)) % 3 == 2)
	{
		out[ft_strlen(out) - 1] = '=';
		out[ft_strlen(out) - 2] = '=';
	}
	else if ((4 * ((in_len + 2) / 3)) % 3 == 1)
		out[ft_strlen(out) - 1] = '=';
	return (out);
}

char	*decode(char *line, size_t len, size_t i)
{
	char	*out;
	int		pad;
	int		n;
	size_t	l;

	pad = len > 0 && (len % 4 || line[len - 1] == '=');
	l = ((len + 3) / 4 - pad) * 4;
	out = ft_strnew(l / 4 * 3 + pad);
	i = 0;
	while (i < l)
		sextet_to_octet(line, &i, out);
	if (pad)
	{
		n = g_b64_d[(int)line[l]] << 18 | g_b64_d[(int)line[l + 1]] << 12;
		out[ft_strlen(out) - 1] = n >> 16;
		if (len > l + 2 && line[l + 2] != '=')
		{
			n |= g_b64_d[(int)line[l + 2]] << 6;
			i = ft_strlen(out);
			out[i] = n >> 8 & 0xFF;
			out[i + 1] = '\0';
		}
	}
	return (out);
}
