/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:01:30 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/23 17:16:13 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	leftrotate(unsigned int x, int n)
{
	return ((x) << n) | ((x) >> (32 - n));
}

int	rightrotate(unsigned int x, int n)
{
	return ((x) >> n) | ((x) << (32 - n));
}

int	xor(int a, int b)
{
	return (a ^ b);
}
