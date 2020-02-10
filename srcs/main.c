/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:27:28 by mfrias            #+#    #+#             */
/*   Updated: 2019/12/14 14:22:39 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_file(int fd)
{
	char	c[2];
	char	*str;
	char	*tmp;

	c[1] = 0;
	str = ft_strdup("");
	while (read(fd, c, 1))
	{
		tmp = str;
		str = ft_strjoin(str, c);
		free(tmp);
	}
	return (str);
}

void	invalid_cmd(int argc, char *cmd)
{
	if (argc < 2)
	{
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
		exit(0);
	}
	else if (ft_strcmp(cmd, "md5") && ft_strcmp(cmd, "sha256") &&
	ft_strcmp(cmd, "base64") && ft_strcmp(cmd, "des") &&
	ft_strcmp(cmd, "des-ecb") && ft_strcmp(cmd, "des-cbc"))
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", cmd);
		ft_putendl("Standard commands:\n");
		ft_putendl("Message Digest commands:");
		ft_printf("md5\nsha256\n\n");
		ft_putendl("Cipher commands:");
		ft_printf("base64\ndes\ndes-ecb\ndes-cbc\n");
		exit(1);
	}
}

t_flag	get_flags(char **argv, int *i)
{
	t_flag	op;

	op = (t_flag) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL};
	while (argv[*i] && argv[*i][0] == '-')
	{
		op.p = !op.p && !ft_strchr(argv[*i], 'p') ? 0 : 1;
		op.q = !op.q && !ft_strchr(argv[*i], 'q') ? 0 : 1;
		op.r = !op.r && !ft_strchr(argv[*i], 'r') ? 0 : 1;
		op.s = !op.s && !ft_strchr(argv[*i], 's') ? 0 : 1;
		op.a = !op.a && !ft_strchr(argv[*i], 'a') ? 0 : 1;
		op.d = !op.d && !ft_strchr(argv[*i], 'd') ? 0 : 1;
		op.e = !op.e && !ft_strchr(argv[*i], 'e') ? 0 : 1;
		if (ft_strchr(argv[*i], 'i'))
			op.in = argv[*i + 1];
		if (ft_strchr(argv[*i], 'o'))
			op.out = argv[*i + 1];
		flag_error(argv[1], &argv[*i][1]);
		(*i)++;
		if (argv[*i])
			if (!ft_strcmp(argv[*i], op.in) || !ft_strcmp(argv[*i], op.out))
				(*i)++;
		if (op.s)
			break ;
	}
	return (op);
}

int		main(int argc, char **argv)
{
	int		i;
	t_flag	flag;

	i = 2;
	invalid_cmd(argc, argv[1]);
	flag = get_flags(&argv[0], &i);
	if (!ft_strcmp(argv[1], "md5"))
		message((t_fun) {argv[1], md5}, &flag, &argv[i]);
	else if (!ft_strcmp(argv[1], "sha256"))
		message((t_fun) {argv[1], sha256}, &flag, &argv[i]);
	else if (!ft_strcmp(argv[1], "base64"))
		base64(&flag);
	else if (!ft_strcmp(argv[1], "des"))
		des(&flag);
	return (1);
}
