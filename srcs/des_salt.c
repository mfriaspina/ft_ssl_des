/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:19:55 by mfrias            #+#    #+#             */
/*   Updated: 2020/03/03 14:26:44 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		convert_hex_char_to_4bit(uint8_t c)
{
	if (c > 47 && c < 58)
		return (c - 48);
	else if (c > 64 && c < 71)
		return (c - 55);
	else if (c > 96 && c < 103)
		return (c - 97);
	return (0);
}

uint64_t	hex_str_to_64bit_le(char *s)
{
	int			i;
	uint64_t	message;
	uint64_t	tmp;

	if (!s)
		return (0);
	i = -1;
	message = 0;
	while (*s && ++i < 8)
	{
		tmp = ((uint64_t)convert_hex_char_to_4bit(*s)) << 4;
		++s;
		if (*s)
			tmp |= (uint64_t)convert_hex_char_to_4bit(*s);
		message |= tmp << (8 * i);
		if (*s)
			++s;
	}
	return (message);
}

char		*get_random(int size)
{
	int		fd;
	char	*str;

	str = ft_strnew(size);
	fd = open("/dev/random", O_RDONLY);
	read(fd, str, size);
	close(fd);
	return (str);
}

char		*get_salt(t_flag *flags)
{
	char	*salt;
	char	buffer[128];

	if (flags->salt)
	{
		if (!is_hex(flags->salt))
			free_exit("non-hex digit\ninvalid hex salt value\n", NULL);
		salt = ft_strtoupper(flags->salt);
		if (ft_strlen(salt) > 16)
			salt[16] = '\0';
		while (ft_strlen(salt) < 16)
			salt = free_strjoin(salt, "0", 0);
		return (salt);
	}
	salt = get_random(8);
	print_bytes((t_ubyte *)salt, 8, buffer);
	free(salt);
	salt = ft_strdup(buffer);
	return (salt);
}

t_ubyte		*get_iv(t_flag *flags)
{
	char	*salt;
	t_ubyte	*iv;

	iv = NULL;
	salt = NULL;
	if (flags->v)
	{
		if (!is_hex(flags->v))
			free_exit("non-hex digit\ninvalid hex iv value\n", NULL);
		salt = ft_strtoupper(flags->v);
		if (ft_strlen(salt) > 16)
			salt[16] = '\0';
		while (ft_strlen(salt) < 16)
			salt = free_strjoin(salt, "0", 0);
		iv = char_to_ubyte(salt);
		free(salt);
	}
	return (iv);
}
