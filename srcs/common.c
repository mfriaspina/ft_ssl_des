/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:45:04 by mfrias            #+#    #+#             */
/*   Updated: 2020/03/02 15:51:13 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*file(t_fun fun, t_flag *flags, char **argv)
{
	char	*str;
	int		fd;

	str = NULL;
	fd = open(argv[0], O_RDONLY);
	if (fd >= 0)
	{
		str = read_file(fd, NULL);
		if (!flags->r && !flags->q)
			ft_printf("%s (%s) = ", fun.name, argv[0]);
	}
	close(fd);
	if (fd < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n",
		fun.name, argv[0]);
		flags->e = 1;
	}
	flags->t = 2;
	return (str);
}

/*
** flags.t types:
** 0 : read from stdin
** 1 : str = argv[i]
** 2 : read from file argv[i]
*/

char	*pre(t_fun fun, t_flag *flags, char **argv)
{
	char	*str;

	if (flags->p)
	{
		str = read_file(0, NULL);
		ft_putstr(str);
		flags->t = 1;
	}
	else if (flags->s)
	{
		str = argv[0];
		if (!flags->r && !flags->q)
			ft_printf("%s (\"%s\") = ", fun.name, str);
		flags->t = 0;
		flags->s = 0;
	}
	else if (argv[0])
		str = file(fun, flags, argv);
	else
	{
		str = read_file(0, NULL);
		flags->t = 1;
	}
	return (str);
}

void	message(t_fun fun, t_flag *flags, char **argv)
{
	char	*str;

	str = pre(fun, flags, argv);
	if (!flags->e)
	{
		fun.f(str, ft_strlen(str));
		if (flags->r && !flags->q && !flags->p && !flags->t)
			ft_printf(" \"%s\"", str);
		else if (flags->r && !flags->q && !flags->p && flags->t)
			ft_printf(" %s", argv[0]);
		if (flags->t > 0)
			ft_strdel(&str);
		ft_putchar('\n');
	}
	if (flags->p && argv[0])
	{
		flags->p = 0;
		message(fun, flags, &argv[0]);
	}
	else if (argv[0] && argv[1])
		message(fun, flags, &argv[1]);
}
