/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:23:56 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/10 16:28:46 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des(t_flag *flags)
{
	char	*line;
	char	*out;
	int		fd;

	fd = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: des: %s: No sush file or directory\n", flags->in);
		return ;
	}
	line = read_file(fd);
	close(fd);
	if (flags->d && !flags->e)
		out = decode_des(line, ft_strlen(line), 0);
	else
		out = encode_des(line, flags);
	print_out(out, flags);
	free(line);
	free(out);
}
