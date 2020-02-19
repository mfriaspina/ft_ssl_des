/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:09:45 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/18 15:42:14 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	des_flags(t_flag *op, char **argv, int *i)
{
	if (ft_strchr(argv[*i], 'p'))
		op->pass = argv[*i + 1];
	if (ft_strchr(argv[*i], 's'))
		op->salt = argv[*i + 1];
	if (ft_strchr(argv[*i], 'k'))
		op->k = argv[*i + 1];
	if (ft_strchr(argv[*i], 'v'))
		op->v = argv[*i + 1];
	if (ft_strchr(argv[*i], 'p') || ft_strchr(argv[*i], 'v') ||
		ft_strchr(argv[*i], 'k') || ft_strchr(argv[*i], 's'))
		op->update = 1;
	op->print = !op->print && !ft_strchr(argv[*i], 'P') ? 0 : 1;
}

static void	start_flags(t_flag *op, char **argv, int *i)
{
	if (ft_strstr(argv[1], "des"))
		des_flags(op, argv, i);
	else
	{
		op->p = !op->p && !ft_strchr(argv[*i], 'p') ? 0 : 1;
		op->s = !op->s && !ft_strchr(argv[*i], 's') ? 0 : 1;
	}
	op->a = !op->a && !ft_strchr(argv[*i], 'a') ? 0 : 1;
	op->d = !op->d && !ft_strchr(argv[*i], 'd') ? 0 : 1;
	op->e = !op->e && !ft_strchr(argv[*i], 'e') ? 0 : 1;
	op->q = !op->q && !ft_strchr(argv[*i], 'q') ? 0 : 1;
	op->r = !op->r && !ft_strchr(argv[*i], 'r') ? 0 : 1;
	if (ft_strchr(argv[*i], 'i'))
		op->in = argv[*i + 1];
	if (ft_strchr(argv[*i], 'o'))
		op->out = argv[*i + 1];
	if (ft_strchr(argv[*i], 'i') || ft_strchr(argv[*i], 'o'))
		op->update = 1;
}

t_flag		get_flags(char **argv, int *i)
{
	t_flag	op;

	op = (t_flag) {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0};
	while (argv[*i] && argv[*i][0] == '-')
	{
		op.update = 0;
		start_flags(&op, argv, i);
		flag_error(argv[1], &argv[*i][1]);
		(*i)++;
		if (op.update)
			(*i)++;
		if (op.s)
			break ;
	}
	return (op);
}
