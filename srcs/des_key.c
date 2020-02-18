/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:46:19 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/17 15:14:01 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ubyte	ft_strtol(char *str)
{
	char	*new;
	t_ubyte ret;
	int		tens;
	int		ones;

	new = ft_strtoupper(str);
	if (str[0] >= '0' && str[0] <= '9')
		tens = str[0] - '0';
	else
		tens = str[0] - 'A' + 10;
	if (str[1] >= '0' && str[1] <= '9')
		ones = str[1] - '0';
	else
		ones = str[1] - 'A' + 10;
	ret = (16 * tens) + ones;
	ft_strdel(&new);
	return (ret);
}

t_ubyte	*char_to_ubyte(char *str)
{
	size_t	i;
	size_t	j;
	t_ubyte	*key;
	char	*temp;

	i = 0;
	j = 0;
	key = NULL;
	key = (t_ubyte *)ft_strnew(8);
	while (i < ft_strlen(str) && j < 8)
	{
		temp = ft_strnew(2);
		ft_strncpy(temp, &str[i], 2);
		key[j++] = ft_strtol(temp);
		ft_strdel(&temp);
		i += 2;
	}
	return (key);
}

t_ubyte	*get_key(t_flag *flags)
{
	t_ubyte	*key;

	if (ft_strlen(flags->k) % 2 != 0)
		return (NULL);
	if (flags->k)
		key = char_to_ubyte(flags->k);
	else
		key = NULL;
	return (key);
}
