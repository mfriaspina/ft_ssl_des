/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:27:28 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/26 19:43:28 by mfrias           ###   ########.fr       */
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
		des_cbc(&flag);
	else if (!ft_strcmp(argv[1], "des-ecb"))
		des(&flag);
	else if (!ft_strcmp(argv[1], "des-cbc"))
		des_cbc(&flag);
	return (EXIT_SUCCESS);
}
