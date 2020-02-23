/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:19:55 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/22 18:08:56 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ubyte	*get_random(int size)
{
	int		fd;
	t_ubyte	*str;

	str = (t_ubyte *)ft_strnew(size);
	fd = open("/dev/random", O_RDONLY);
	read(fd, str, size);
	close(fd);
	return (str);
}

t_ubyte	*get_salt(t_flag *flags)
{
	t_ubyte	*salt;

	if (flags->salt)
	{
		if (!is_hex(flags->salt))
			free_exit("non-hex digit\ninvalid hex salt value\n", NULL);
		salt = char_to_ubyte(flags->salt);
	}
	else
		salt = get_random(8);
	return (salt);
}

t_ubyte	*get_iv(t_flag *flags)
{
	t_ubyte	*salt;
	int		i;

	if (flags->v)
	{
		i = -1;
		if (!is_hex(flags->v))
			free_exit("non-hex digit\ninvalid hex iv value\n", NULL);
		salt = char_to_ubyte(flags->v);
	}
	else
		salt = get_random(8);
	return (salt);
}
