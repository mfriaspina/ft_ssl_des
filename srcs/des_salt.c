/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:19:55 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/19 12:52:42 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*get_random(int size)
{
	int		fd;
	char	*str;

	str = ft_strnew(size);
	fd = open("/dev/random", O_RDONLY);
	read(fd, str, size);
	close(fd);
	return (str);
}

t_ubyte	*get_salt(t_flag *flags)
{
	t_ubyte	*salt;

	if (flags->salt)
		salt = char_to_ubyte(flags->salt);
	else
		salt = (t_ubyte *)get_random(8);
	return (salt);
}
