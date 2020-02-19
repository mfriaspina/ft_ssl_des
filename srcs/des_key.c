/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:46:19 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/19 14:30:43 by mfrias           ###   ########.fr       */
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
	if (new[0] >= '0' && new[0] <= '9')
		tens = new[0] - '0';
	else if (new[0] >= 'A' && new[0] <= 'F')
		tens = new[0] - 'A' + 10;
	else
		tens = 0;
	if (new[1] >= '0' && new[1] <= '9')
		ones = new[1] - '0';
	else if (new[1] >= 'A' && new[1] <= 'F')
		ones = new[1] - 'A' + 10;
	else
		ones = 0;
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

t_ubyte	*salted_key(t_flag *flags, t_ubyte *salt)
{
	t_ubyte	*key;
	char	*str;
	char	*conf;

	if (flags->k)
		str = ft_strdup(flags->k);
	else if (flags->pass)
		str = ft_strdup(flags->pass);
	else
	{
		str = ft_strdup(getpass("enter des-ecb encryption password:"));
		conf = getpass("Verifying - enter des-ecb encryption password:");
		if (ft_strcmp(str, conf))
		{
			ft_printf("Verify failure\nbad password read\n");
			free(salt);
			exit(EXIT_FAILURE);
		}
		conf = NULL;
	}
	key = char_to_ubyte(str);
	free(str);
	return (key);
}

t_ubyte	*get_key(t_flag *flags)
{
	t_ubyte	*key;
	t_ubyte	*salt;
	char	buffer[128];

	salt = get_salt(flags);
	key = salted_key(flags, salt);
	if (flags->print)
	{
		print_bytes(salt, 8, buffer);
		ft_printf("salt=%s\n", buffer);
		print_bytes(key, 8, buffer);
		ft_printf("key=%s\n", buffer);
	}
	free(salt);
	return (key);
}
