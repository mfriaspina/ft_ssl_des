/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_crypt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:19:32 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/23 18:22:28 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ubyte	*pbkdf2(char *pass, uint64_t salt, char **iv)
{
	char		*input;
	char		*output;
	size_t		len;
	t_ubyte		*key;

	len = ft_strlen(pass) + 8;
	input = ft_strnew(len);
	ft_memcpy(input, pass, ft_strlen(pass));
	ft_memcpy(&input[ft_strlen(pass)], &salt, 8);
	output = execute_md5(input, len, 0, 0);
	free(input);
	input = ft_strtoupper(output);
	free(output);
	output = ft_strnew(16);
	ft_memcpy(output, input, 16);
	if (!(*iv))
	{
		*iv = ft_strnew(16);
		ft_memcpy(*iv, &input[16], 16);
	}
	key = char_to_ubyte(output);
	free(output);
	free(input);
	free(pass);
	return (key);
}
