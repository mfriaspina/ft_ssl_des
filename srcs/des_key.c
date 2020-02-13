/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:22:14 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/13 12:11:32 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int g_shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int g_pc1[] =
{
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43,
	35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54,
	46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

int g_pc2[] =
{
	14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7,
	27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39,
	56, 34, 53, 46, 42, 50, 36, 29, 32};

int g_key56bit[56];
int g_key48bit[17][48];

void	key56to48(int round, int pos, int text)
{
	int i;

	i = -1;
	while (++i < 56)
		if (g_pc2[i] == pos + 1)
			break ;
	g_key48bit[round][i] = text;
}

void	key64to56(int pos, int text)
{
	int i;

	i = -1;
	while (++i < 56)
		if (g_pc1[i] == pos + 1)
			break ;
	g_key56bit[i] = text;
}

void	key64to48(unsigned int key[])
{
	int k, backup[17][2];
	int cd[17][56];
	int c[17][28], d[17][28];

	for (int i = 0; i < 64; i++)
		key64to56(i, key[i]);

	for (int i = 0; i < 56; i++)
		if (i < 28)
			c[0][i] = g_key56bit[i];
		else
			d[0][i - 28] = g_key56bit[i];

	for (int x = 1; x < 17; x++) 
	{
		int shift = g_shifts[x - 1];

		for (int i = 0; i < shift; i++)
			backup[x - 1][i] = c[x - 1][i];
		for (int i = 0; i < (28 - shift); i++)
			c[x][i] = c[x - 1][i + shift];
		k = 0;
		for (int i = 28 - shift; i < 28; i++)
			c[x][i] = backup[x - 1][k++];

		for (int i = 0; i < shift; i++)
			backup[x - 1][i] = d[x - 1][i];
		for (int i = 0; i < (28 - shift); i++)
			d[x][i] = d[x - 1][i + shift];
		k = 0;
		for (int i = 28 - shift; i < 28; i++)
			d[x][i] = backup[x - 1][k++];
	}

	for (int j = 0; j < 17; j++) 
	{
		for (int i = 0; i < 28; i++)
			cd[j][i] = c[j][i];
		for (int i = 28; i < 56; i++)
			cd[j][i] = d[j][i - 28];
	}

	for (int j = 1; j < 17; j++)
		for (int i = 0; i < 56; i++)
			key56to48(j, i, cd[j][i]);
}

char	*get_key(void)
{
	char			*temp;
	unsigned int	key[64];
	int				i;

	temp = getpass("enter des password:");
	ft_printf("%s\n", temp);
	i = -1;
	while (++i < (int)ft_strlen(temp))
		key[i] = temp[i] - 48;
	key64to48(key);
	i = -1;
	while (++i < 64)
		ft_printf("%u", key[i]);
	return (temp);
}
