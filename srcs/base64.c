/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:42:44 by mfrias            #+#    #+#             */
/*   Updated: 2019/12/14 14:19:05 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_out(char *out, t_flag *flags)
{
	int	fd;

	fd = 1;
	if (flags->out)
		fd = open(flags->out, O_WRONLY);
	if (fd < 0)
	{
		fd = open(flags->out, O_CREAT);
		fd = open(flags->out, O_WRONLY);
	}
	ft_putendl_fd(out, fd);
	close(fd);
}

void	base64(t_flag *flags)
{
	char	*line;
	char	*out;
	int		fd;

	fd = 0;
	if (flags->in)
		fd = open(flags->in, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: base64: %s: No such file or directory\n", flags->in);
		return ;
	}
	line = read_file(fd);
	close(fd);
	if (flags->d && !flags->e)
		out = decode(line, ft_strlen(line), 0);
	else
		out = encode(line, ft_strlen(line));
	print_out(out, flags);
	free(line);
	free(out);
}
