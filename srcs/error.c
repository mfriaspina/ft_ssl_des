/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:54:16 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/13 14:10:42 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	b64_e(char *f)
{
	int		i;

	i = -1;
	while (f[++i])
		if (f[i] != 'e' && f[i] != 'd' && f[i] != 'i' && f[i] != 'o')
			break ;
	if (!f[i])
		return (0);
	ft_printf("base64: invalid option -%c\n", f[i]);
	ft_printf("Usage:	ft_ssl base64 [-ed] [-i in_file] [-o out_file]\n");
	ft_printf("-e, encodes input\n");
	ft_printf("-d, decodes input\n");
	ft_printf("-i, input file\n");
	ft_printf("-o, output file\n");
	return (1);
}

static int	des_e(char *f)
{
	int i;

	i = -1;
	while (f[++i])
		if (f[i] != 'e' && f[i] != 'd' && f[i] != 'i' && f[i] != 'o' &&
			f[i] != 'a' && f[i] != 'k' && f[i] != 'p' && f[i] != 's' &&
			f[i] != 'v')
			break ;
	if (!f[i])
		return (0);
	ft_printf("des: invalid option -%c\n", f[i]);
	ft_printf("Usage:	ft_ssl des [-ade] [-i in_file] [-o out_file] [-k key");
	ft_printf("_hex] [-p pass_ascii] [-s salt_hex] [-v vector_hex]\n");
	ft_printf("-a, decode/encode the input/output in base64\n");
	ft_printf("-e, encodes input\n");
	ft_printf("-d, decodes input\n");
	ft_printf("-i, input file\n");
	ft_printf("-o, output file\n");
	ft_printf("-k, key in hex is the next arguement\n");
	ft_printf("-p, password in ascii is the next argument\n");
	ft_printf("-s, the salt in hex is the next argument\n");
	ft_printf("-v, initialization vector in hex is the next argument.\n");
	return (1);
}

void		flag_error(char *name, char *flags)
{
	if (!ft_strcmp(name, "base64") && b64_e(flags))
		exit(-1);
	if (ft_strstr(name, "des") && des_e(flags))
		exit(-1);
}
