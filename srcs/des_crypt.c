/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_crypt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:19:32 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/22 19:29:05 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ubyte	*pbkdf2(char *pass, t_ubyte *salt)
{
	char		*input;
	char		*output;
	size_t		i;
	size_t		len;
	t_ubyte		*key;

	len = ft_strlen(pass) + 8;
	input = ft_strnew(len);
	ft_memcpy(input, pass, ft_strlen(pass));
	ft_memcpy(&input[ft_strlen(pass)], salt, 8);
	i = -1;
	while (++i < PBKDF_IT)
	{
		ft_printf("%s\n", input);
		output = execute_md5(input, len, 0, 0);
		ft_printf("%s\n", output);
		free(input);
		input = output;
		len = 32;
	}
	key = (t_ubyte *)ft_strnew(len / 2);
	ft_memcpy(key, "temp", len / 2);
	free(output);
	free(pass);
	return (key);
}
