/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:54:16 by mfrias            #+#    #+#             */
/*   Updated: 2019/12/14 14:10:50 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		b64_e(char *f)
{
	int		i;

	i = -1;
	while (f[++i])
		if (f[i] != 'e' && f[i] != 'd' && f[i] != 'i' && f[i] != 'o')
			break ;
	if (!f[i])
		return (0);
	ft_printf("base64: invalid option -- %c\n", f[i]);
	ft_printf("Usage:	ft_ssl base64 [-ed] [-i in_file] [-o out_file]\n");
	ft_printf("-e, --encode   encodes input\n");
	ft_printf("-d, --decode   decodes input\n");
	ft_printf("-i, --input    input file (default: \"-\" for stdin)\n");
	ft_printf("-o, --output   output file (default: \"-\" for stdout)\n");
	return (1);
}

void	flag_error(char *name, char *flags)
{
	if (!ft_strcmp(name, "base64") && b64_e(flags))
		exit(-1);
}
