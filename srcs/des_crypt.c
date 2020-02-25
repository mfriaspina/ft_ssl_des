/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_crypt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:19:32 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/24 13:03:21 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	pbkdf2(t_des *des, uint64_t salt)
{
	char		*input;
	char		*output;
	size_t		len;
	t_ubyte		*key;

	len = ft_strlen(des->str) + 8;
	input = ft_strnew(len);
	ft_memcpy(input, des->str, ft_strlen(des->str));
	ft_memcpy(&input[ft_strlen(des->str)], &salt, 8);
	output = execute_md5(input, len, 0, 0);
	free(input);
	input = ft_strtoupper(output);
	free(output);
	output = ft_strnew(16);
	ft_memcpy(output, input, 16);
	if (!(des->iv))
	{
		des->iv = ft_strnew(16);
		ft_memcpy(des->iv, &input[16], 16);
	}
	key = char_to_ubyte(output);
	free(output);
	free(input);
	des->key = key;
}
