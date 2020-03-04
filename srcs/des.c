/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:23:56 by mfrias            #+#    #+#             */
/*   Updated: 2020/03/04 12:06:16 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** TODO
** 1) Des large input
*/

char		*enc_out(t_flag *flags, t_des *des, t_string *enc)
{
	char		*str;
	char		*salted;
	uint64_t	salt;

	str = ft_strdup((char *)enc->data);
	if (flags->pass && !flags->d && !flags->k)
	{
		salted = ft_strnew(16 + enc->len);
		salt = hex_str_to_64bit_le(des->salt);
		ft_memcpy(salted, "Salted__", 8);
		ft_memcpy(&salted[8], &salt, 8);
		ft_memcpy(&salted[16], str, enc->len);
		free(str);
		enc->len += 16;
		return (salted);
	}
	return (str);
}

void		print_des(t_flag *flags, t_des *des, t_string enc)
{
	int		fd;
	char	*str;
	char	*out;

	fd = 1;
	if (flags->out)
		fd = open(flags->out, O_WRONLY);
	if (fd < 0)
	{
		fd = open(flags->out, O_CREAT);
		fd = open(flags->out, O_WRONLY);
	}
	str = enc_out(flags, des, &enc);
	if (flags->a && !flags->d)
	{
		out = encode(str, enc.len);
		ft_putendl_fd(out, fd);
		free(out);
	}
	else
		write(fd, str, enc.len);
	if (fd != 1)
		close(fd);
	free(enc.data);
	free(str);
}

char		*read_des(t_flag *flags, int *len)
{
	char		*in;
	char		*temp;
	int			fd;

	fd = 0;
	*len = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: des: %s: No such file or directory\n", flags->in);
		return (NULL);
	}
	if (flags->a && flags->d)
	{
		in = read_file(fd, len);
		temp = decode(in, ft_strlen(in));
		free(in);
		in = temp;
	}
	else
		in = read_file(fd, len);
	close(fd);
	*len = flags->d && !flags->k ? *len - 16 : *len;
	return (in);
}

void		des(t_flag *flags)
{
	char		*in;
	t_des		*des;
	t_string	enc;
	int			len;

	if (!(in = read_des(flags, &len)))
		return ;
	des = get_key(flags, in);
	if (flags->d && !flags->k)
		in += 16;
	des->mode = 0;
	if (flags->d && !flags->e)
		enc = des_decrypt(des, (t_ubyte *)in, len);
	else
		enc = des_encrypt(des, (t_ubyte *)in, len);
	print_des(flags, des, enc);
	if (flags->d && !flags->k)
		in -= 16;
	free(in);
	check_free(des);
}

void		des_cbc(t_flag *flags)
{
	char		*in;
	t_des		*des;
	t_string	enc;
	int			len;

	if (!(in = read_des(flags, &len)))
		return ;
	des = get_key(flags, in);
	if (!(des->iv))
		free_exit("iv undefined\n", des);
	if (flags->d && !flags->k)
		in += 16;
	des->mode = 1;
	if (flags->d && !flags->e)
		enc = des_decrypt(des, (t_ubyte *)in, len);
	else
		enc = des_encrypt(des, (t_ubyte *)in, len);
	print_des(flags, des, enc);
	if (flags->d && !flags->k)
		in -= 16;
	free(in);
	check_free(des);
}
