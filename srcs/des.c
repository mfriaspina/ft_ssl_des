/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:23:56 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/18 11:42:26 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_des(t_flag *flags, t_string enc)
{
	int		fd;
	char	*str;

	fd = 1;
	if (flags->out)
		fd = open(flags->out, O_WRONLY);
	if (fd < 0)
	{
		fd = open(flags->out, O_CREAT);
		fd = open(flags->out, O_WRONLY);
	}
	str = (char *)enc.data;
	if (flags->a)
		ft_putendl_fd(encode(str, ft_strlen(str)), fd);
	else
		ft_putendl_fd(str, fd);
	if (fd != 1)
		close(fd);
	if (enc.len > 0)
		free(enc.data);
}

void		des(t_flag *flags)
{
	char		*in;
	int			fd;
	t_ubyte		*key;
	t_string	enc;

	if (!(key = get_key(flags)))
	{
		ft_printf("ft_ssl: des: Invalid key\n");
		return ;
	}
	fd = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: des: %s: No such file or directory\n", flags->in);
		return ;
	}
	in = read_file(fd);
	close(fd);
	if (flags->d && !flags->e)
		enc = des_decrypt(key, (t_ubyte *)in, ft_strlen(in));
	else
		enc = des_encrypt(key, (t_ubyte *)in, ft_strlen(in));
	print_des(flags, enc);
	free(in);
	free(key);
}
