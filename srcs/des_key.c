/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:46:19 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/26 18:59:02 by mfrias           ###   ########.fr       */
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
	key = (t_ubyte *)ft_strnew(8);
	while (i < ft_strlen(str) && j < 8)
	{
		temp = ft_strnew(2);
		ft_strncpy(temp, &str[i], 2);
		if (!is_hex(temp))
		{
			ft_strdel(&temp);
			free(key);
			free(str);
			return (NULL);
		}
		key[j++] = ft_strtol(temp);
		ft_strdel(&temp);
		i += 2;
	}
	return (key);
}

void	pass_salted_key(t_flag *flags, t_des *des, char *in)
{
	if (ft_strncmp(in, "Salted__", 8))
	{
		free(in);
		free_exit("bad magic number\n", des);
	}
	free(des->salt);
	des->salt = ft_strnew(9);
	print_bytes((t_ubyte *)&in[8], 8, des->salt);
	if (flags->pass)
		des->str = ft_strdup(flags->pass);
	else
		des->str = ft_strdup(getpass("enter des-ecb decryption password:"));
	pbkdf2(des, hex_str_to_64bit_le(des->salt));
}

void	salted_key(t_flag *flags, t_des *des)
{
	char	*conf;

	if (flags->k)
	{
		conf = ft_strdup(flags->k);
		if (!(des->key = char_to_ubyte(conf)))
			free_exit("non-hex digit\ninvalid hex key value\n", des);
		free(conf);
		return ;
	}
	else if (flags->pass)
		des->str = ft_strdup(flags->pass);
	else
	{
		des->str = ft_strdup(getpass("enter des-ecb encryption password:"));
		conf = getpass("verifying - enter des-ecb encryption password:");
		if (ft_strcmp(des->str, conf))
			free_exit("verify failure\nbad password read\n", des);
		conf = NULL;
	}
	pbkdf2(des, hex_str_to_64bit_le(des->salt));
}

t_des	*get_key(t_flag *flags, char *in)
{
	t_des	*des;
	char	buffer[128];

	des = (t_des *)ft_memalloc(sizeof(t_des));
	des->salt = get_salt(flags);
	des->iv = get_iv(flags);
	if (flags->d && !flags->k)
		pass_salted_key(flags, des, in);
	else
		salted_key(flags, des);
	if (flags->print)
	{
		ft_printf("salt=%s\n", des->salt);
		print_bytes(des->key, 8, buffer);
		ft_printf("key=%s\n", buffer);
		ft_printf("iv=%s\n", des->iv);
	}
	ft_strdel(&des->str);
	return (des);
}
