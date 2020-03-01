/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:23:56 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/29 12:39:46 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** TODO
** 1) Des large input
*/

char		*enc_out(t_flag *flags, t_des *des, t_string *enc, int i)
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
	if (flags->d && flags->a)
	{
		while (str[++i])
			if (str[i] == '\n')
				str[i + 1] = '\0';
		enc->len = i;
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
	str = enc_out(flags, des, &enc, -1);
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

char		*read_des(t_flag *flags)
{
	char		*in;
	char		*temp;
	int			fd;

	fd = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: des: %s: No such file or directory\n", flags->in);
		return (NULL);
	}
	if (flags->a && flags->d)
	{
		get_next_line(fd, &in);
		temp = decode(in, ft_strlen(in));
		free(in);
		in = temp;
	}
	else
		get_next_line(fd, &in);
	close(fd);
	return (in);
}

void		des(t_flag *flags)
{
	char		*in;
	t_des		*des;
	t_string	enc;

	if (!(in = read_des(flags)))
		return ;
	des = get_key(flags, in);
	if (flags->d && !flags->k)
		in += 16;
	des->mode = 0;
	if (flags->d && !flags->e)
		enc = des_decrypt(des, (t_ubyte *)in, ft_strlen(in));
	else
		enc = des_encrypt(des, (t_ubyte *)in, ft_strlen(in));
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

	if (!(in = read_des(flags)))
		return ;
	des = get_key(flags, in);
	if (!(des->iv))
		free_exit("iv undefined\n", des);
	if (flags->d && !flags->k)
		in += 16;
	des->mode = 1;
	if (flags->d && !flags->e)
		enc = des_decrypt(des, (t_ubyte *)in, ft_strlen(in));
	else
		enc = des_encrypt(des, (t_ubyte *)in, ft_strlen(in));
	print_des(flags, des, enc);
	if (flags->d && !flags->k)
		in -= 16;
	free(in);
	check_free(des);
}
