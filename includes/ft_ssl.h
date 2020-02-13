/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:26:37 by mfrias            #+#    #+#             */
/*   Updated: 2020/02/13 14:34:15 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <fcntl.h>
# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RIGHTROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))

typedef struct	s_flag
{
	char		update;
	char		p;
	char		q;
	char		r;
	char		s;
	char		t;
	char		a;
	char		e;
	char		d;
	char		*k;
	char		*v;
	char		*in;
	char		*out;
	char		*pass;
	char		*salt;
}				t_flag;

typedef struct	s_fun
{
	char		*name;
	void		(*f)();
}				t_fun;

t_flag			get_flags(char **argv, int *i);
void			flag_error(char *name, char *flags);
char			*read_file(int fd);

void			md5(char *old_msg, size_t initial_len);

void			sha256(char *old_msg, size_t initial_len);

void			message(t_fun fun, t_flag *flags, char **argv);

uint32_t		get_g(int i);
uint32_t		get_f(uint32_t *val, int i);
void			get_val(uint32_t *o, uint32_t *val);
uint32_t		*get_w(uint32_t *msg, int i);
uint32_t		sha_rev(uint32_t n);

char			*encode(char *line, size_t in_len);
char			*decode(char *line, size_t len, size_t i);
void			base64(t_flag *flags);

char			*get_key(void);
void			des(t_flag *flags);

#endif
