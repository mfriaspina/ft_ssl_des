/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:42:44 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/26 13:34:55 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_out(char *out, t_flag *flags)
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
	if (out[ft_strlen(out) - 1] == '\n')
		ft_putstr_fd(out, fd);
	else
		ft_putendl_fd(out, fd);
	if (fd != 1)
		close(fd);
}

static char	*remove_whitespaces(char *str)
{
	int	i;
	int	j;

	i = -1;
	while ((size_t)++i < ft_strlen(str))
	{
		if (str[i] == ' ')
		{
			j = i - 1;
			while (str[++j] != '\0')
				str[j] = str[j + 1];
		}
	}
	return (str);
}

void		base64(t_flag *flags)
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
	get_next_line(fd, &line);
	close(fd);
	if (flags->d && !flags->e)
		out = decode(remove_whitespaces(line), ft_strlen(line));
	else
		out = encode(line, ft_strlen(line));
	print_out(out, flags);
	free(line);
	free(out);
}
