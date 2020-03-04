/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:26:37 by mfrias            #+#    #+#             */
/*   Updated: 2020/03/03 13:49:07 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"
# include <fcntl.h>
# define KEY_LEN 8

typedef struct			s_flag
{
	char				update;
	char				p;
	char				q;
	char				r;
	char				s;
	char				t;
	char				a;
	char				e;
	char				d;
	char				*k;
	char				*v;
	char				*in;
	char				*out;
	char				*pass;
	char				*salt;
	char				print;
}						t_flag;

typedef struct			s_fun
{
	char				*name;
	void				(*f)();
}						t_fun;

typedef struct			s_base64
{
	size_t				i;
	size_t				j;
	size_t				k;
	uint64_t			res_a;
	uint64_t			res_b;
	uint64_t			res_c;
	uint64_t			res_d;
	uint64_t			res_e;
	int					input_len;
	int					output_len;
}						t_base64;

typedef	unsigned char	t_ubyte;
typedef t_ubyte			t_subkey[17][6];

typedef struct			s_des
{
	t_ubyte				*key;
	t_subkey			ks;
	char				*salt;
	t_ubyte				*iv;
	t_ubyte				*temp;
	char				*str;
	int					mode;
}						t_des;

typedef struct			s_des_algo
{
	t_ubyte				left[17][4];
	t_ubyte				right[17][4];
	t_ubyte				mp[8];
	t_ubyte				e[8];
}						t_des_algo;

typedef struct			s_string
{
	t_ubyte				*data;
	int					len;
}						t_string;

int						leftrotate(unsigned int x, int n);
int						rightrotate(unsigned int x, int n);
int						xor(int x, int c);

t_flag					get_flags(char **argv, int *i);
void					flag_error(char *name, char *flags);
char					*read_file(int fd, int *len);

void					md5(char *old_msg, size_t initial_len);
char					*execute_md5(char *old_msg, size_t initial_len,
						size_t offset, size_t new_len);

void					sha256(char *old_msg, size_t initial_len);

void					message(t_fun fun, t_flag *flags, char **argv);

uint32_t				get_g(int i);
uint32_t				get_f(uint32_t *val, int i);
void					get_val(uint32_t *o, uint32_t *val);
uint32_t				*get_w(uint32_t *msg, int i);
uint32_t				sha_rev(uint32_t n);

char					*encode(char *input, size_t in_len);
char					*decode(char *input, size_t in_len);
void					base64(t_flag *flags);

char					to_hex(t_ubyte in);
void					print_bytes(t_ubyte *ptr, int len, char *out);
int						peek_bit(const t_ubyte *src, int index);
void					poke_bit(t_ubyte *dst, int index, int value);
void					shift_left(const t_ubyte *src, int len, int times,
						t_ubyte *dst);

void					f(t_ubyte *r, t_ubyte *ks, t_ubyte *sp);
void					get_sub_keys(const t_ubyte *key, t_subkey ks);
void					process_message(const t_ubyte *message, t_subkey ks,
						t_ubyte *ep);

int						is_hex(char *str);
void					free_exit(char *str, t_des *des);
void					check_free(t_des *des);

t_ubyte					*char_to_ubyte(char *str);
t_des					*get_key(t_flag *flags, char *in);

void					pbkdf2(t_des *des, uint64_t salt);

uint64_t				hex_str_to_64bit_le(char *s);
char					*get_salt(t_flag *flags);
t_ubyte					*get_iv(t_flag *flags);

void					process_cbc(t_des *des, t_ubyte *str);
void					process_cbc_dec(t_des *des, t_ubyte *str);
void					cbc_dec(t_des *des, t_ubyte *str);
t_string				des_encrypt(t_des *des, t_ubyte *message, int len);
t_string				des_decrypt(t_des *des, t_ubyte *message, int len);

void					des(t_flag *flags);
void					des_cbc(t_flag *flags);

#endif
