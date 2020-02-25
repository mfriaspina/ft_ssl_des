/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:23:56 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/25 11:00:26 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** TODO = Decrypt from key in b64, Decrypt with password
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
	if (flags->a)
	{
		out = encode(str, enc.len);
		ft_putendl_fd(out, fd);
		free(out);
	}
	else
		ft_putstr_fd(str, fd);
	if (fd != 1)
		close(fd);
	free(enc.data);
	free(str);
}

char		*read_des(t_flag *flags)
{
	char		*in;
	int			fd;

	fd = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: des: %s: No such file or directory\n", flags->in);
		return (NULL);
	}
	in = read_file(fd);
	close(fd);
	return (in);
}

void		des(t_flag *flags)
{
	char		*in;
	t_des		*des;
	t_string	enc;

	if (!(des = get_key(flags)))
	{
		check_free(des);
		return ;
	}
	if (!(in = read_des(flags)))
	{
		free(in);
		check_free(des);
		return ;
	}
	if (flags->d && !flags->e)
		enc = des_decrypt(des->key, (t_ubyte *)in, ft_strlen(in));
	else
		enc = des_encrypt(des->key, (t_ubyte *)in, ft_strlen(in));
	print_des(flags, des, enc);
	free(in);
	check_free(des);
}
