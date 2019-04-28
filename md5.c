/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:53:52 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/25 14:53:56 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

t_md5	*init_md5(t_ssl *ssl)
{
	t_md5	*md5;
	size_t	i;

	if (!(md5 = (t_md5 *)malloc(sizeof(t_md5))))
	{
		ft_error(2, "Malloc error. Sustem dom't give memory");
		return (NULL);
	}
	ft_bzero(md5, sizeof(t_md5));
	i = ft_strlen(ssl->input);
	ssl->input_len = (i * 8 + 1);
	while (ssl->input_len % 512 != 448)
		ssl->input_len++;
	ssl->input_len = ssl->input_len / 8;
	md5->a = 0x67452301;
	md5->b = 0xefcdab89;
	md5->c = 0x98badcfe;
	md5->d = 0x10325476;
	md5->input = (unsigned char *)ft_strnew(ssl->input_len + 64);
	ft_memcpy(md5->input, ssl->input, ft_strlen(ssl->input));
	md5->input[i] = 128;
	i *= 8;
	ft_memcpy(&md5->input[ssl->input_len], &i, 4);
	return (md5);
}

void	do_algo(uint32_t *buf, t_md5 *md5, uint32_t x, uint32_t y)
{
	int			i;
	uint32_t	tmp;

	i = -1;
	while (++i < 64)
	{
		if (i < 16 && (x = F(md5->bb, md5->cc, md5->dd)))
			y = i;
		else if (i < 32 && (x = G(md5->bb, md5->cc, md5->dd)))
			y = (i * 5 + 1) % 16;
		else if (i < 48 && (x = H(md5->bb, md5->cc, md5->dd)))
			y = (3 * i + 5) % 16;
		else if (i < 64 && (x = I(md5->bb, md5->cc, md5->dd)))
			y = (i * 7) % 16;
		tmp = md5->dd;
		md5->dd = md5->cc;
		md5->cc = md5->bb;
		md5->bb += ROTATE((md5->aa + x + g_k_md5[i] + buf[y]), (g_num_md5[i]));
		md5->aa = tmp;
	}
}

void	print_md5_2(t_md5 *md5, t_ssl *ssl)
{
	unsigned char	*str;
	char			*print;
	int				i;

	i = -1;
	str = (unsigned char *)&md5->c;
	while (3 > i++)
	{
		print = ft_itoa_base(str[i], 16);
		ssl->output = ft_strcat(ssl->output, print);
		ft_strdel(&print);
	}
	i = -1;
	str = (unsigned char *)&md5->d;
	while (3 > i++)
	{
		print = ft_itoa_base(str[i], 16);
		ssl->output = ft_strcat(ssl->output, print);
		ft_strdel(&print);
	}
}

void	print_md5(t_md5 *md5, t_ssl *ssl)
{
	unsigned char	*str;
	char			*print;
	int				i;

	i = -1;
	str = (unsigned char *)&(md5->a);
	while (3 > i++)
	{
		print = ft_itoa_base(str[i], 16);
		ssl->output = ft_strcat(ssl->output, print);
		ft_strdel(&print);
	}
	i = -1;
	str = (unsigned char *)&md5->b;
	while (3 > i++)
	{
		print = ft_itoa_base(str[i], 16);
		ssl->output = ft_strcat(ssl->output, print);
		ft_strdel(&print);
	}
	print_md5_2(md5, ssl);
}

void	ft_md5(void *in)
{
	uint32_t	*buf;
	int			move;
	t_md5		*md5;
	t_ssl		*ssl;

	ssl = (t_ssl *)in;
	move = 0;
	if (!(md5 = init_md5(ssl)))
		return ;
	while (ssl->input_len > move)
	{
		buf = (uint32_t *)(md5->input + move);
		md5->aa = md5->a;
		md5->bb = md5->b;
		md5->cc = md5->c;
		md5->dd = md5->d;
		do_algo(buf, md5, 0, 0);
		md5->a += md5->aa;
		md5->b += md5->bb;
		md5->c += md5->cc;
		md5->d += md5->dd;
		move += CHUNK_SIZE;
	}
	print_md5(md5, ssl);
	free(md5);
}
