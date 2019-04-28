/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:42:14 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 16:42:17 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "sha256.h"

void		do_algo_sha256_3(int i, t_sha256 *sha, uint8_t chunk[8], size_t len)
{
	if (i > 0)
	{
		chunk[7] = (uint8_t)(len << 3);
		len >>= 5;
		while (i >= 0)
		{
			chunk[i] = (uint8_t)len;
			len >>= 8;
			i--;
		}
		return ;
	}
	sha->i = -1;
	while (sha->i++ < 7)
		sha->h[sha->i] += sha->ah[sha->i];
	sha->i = -1;
	sha->j = 0;
	while (sha->i++ < 7)
	{
		sha->hash[sha->j++] = (uint8_t)(sha->h[sha->i] >> 24);
		sha->hash[sha->j++] = (uint8_t)(sha->h[sha->i] >> 16);
		sha->hash[sha->j++] = (uint8_t)(sha->h[sha->i] >> 8);
		sha->hash[sha->j++] = (uint8_t)sha->h[sha->i];
	}
}

t_sha256	*init_sha256(t_ssl *ssl)
{
	t_sha256	*sha;

	if (!(sha = (t_sha256 *)malloc(sizeof(t_sha256))))
	{
		ft_error(2, "Malloc error. Sustem dom't give memory");
		return (NULL);
	}
	ft_bzero(sha, sizeof(t_sha256));
	sha->len = ft_strlen(ssl->input);
	ssl->input_len = (sha->len * 8 + 1);
	while (ssl->input_len % 512 != 448)
		ssl->input_len++;
	ssl->input_len = ssl->input_len / 8;
	sha->p = (uint8_t *)ft_strnew(ssl->input_len + 64);
	ft_memcpy(sha->p, ssl->input, sha->len);
	sha->p[sha->len] = 128;
	sha->len *= 8;
	sha->len = ft_strlen(ssl->input);
	do_algo_sha256_3(6, NULL, &sha->p[ssl->input_len], sha->len);
	sha->i = -1;
	while (++sha->i < 8)
		sha->h[sha->i] = g_h[sha->i];
	return (sha);
}

void		do_algo_sha256_2(t_sha256 *sha)
{
	sha->i = -1;
	while (sha->i++ < 63)
	{
		sha->s1 = ROTATE_R(sha->ah[4], 6) ^ ROTATE_R(sha->ah[4], 11) ^
		ROTATE_R(sha->ah[4], 25);
		sha->ch = (sha->ah[4] & sha->ah[5]) ^ (~sha->ah[4] & sha->ah[6]);
		sha->temp1 = sha->ah[7] + sha->s1 + sha->ch + g_k[sha->i] +
		sha->w[sha->i];
		sha->s0 = ROTATE_R(sha->ah[0], 2) ^ ROTATE_R(sha->ah[0], 13) ^
		ROTATE_R(sha->ah[0], 22);
		sha->maj = (sha->ah[0] & sha->ah[1]) ^ (sha->ah[0] & sha->ah[2]) ^
		(sha->ah[1] & sha->ah[2]);
		sha->temp2 = sha->s0 + sha->maj;
		sha->ah[7] = sha->ah[6];
		sha->ah[6] = sha->ah[5];
		sha->ah[5] = sha->ah[4];
		sha->ah[4] = sha->ah[3] + sha->temp1;
		sha->ah[3] = sha->ah[2];
		sha->ah[2] = sha->ah[1];
		sha->ah[1] = sha->ah[0];
		sha->ah[0] = sha->temp1 + sha->temp2;
	}
	do_algo_sha256_3(0, sha, 0, 0);
}

void		do_algo_sha256(t_sha256 *sha)
{
	sha->i = -1;
	while (++sha->i < 16)
	{
		sha->w[sha->i] = (uint32_t)sha->p[0] << 24 |
		(uint32_t)sha->p[1] << 16 | (uint32_t)sha->p[2] << 8 |
		(uint32_t)sha->p[3];
		sha->p += 4;
	}
	sha->i = 15;
	while (++sha->i < 64)
	{
		sha->s0 = ROTATE_R(sha->w[sha->i - 15], 7) ^
		ROTATE_R(sha->w[sha->i - 15], 18) ^ (sha->w[sha->i - 15] >> 3);
		sha->s1 = ROTATE_R(sha->w[sha->i - 2], 17) ^
		ROTATE_R(sha->w[sha->i - 2], 19) ^ (sha->w[sha->i - 2] >> 10);
		sha->w[sha->i] = sha->w[sha->i - 16] + sha->s0 + sha->w[sha->i - 7] +
		sha->s1;
	}
	sha->i = -1;
	while (++sha->i < 8)
		sha->ah[sha->i] = sha->h[sha->i];
	do_algo_sha256_2(sha);
}

void		ft_sha256(void *in)
{
	t_sha256	*sha;
	t_ssl		*ssl;
	int			i;

	ssl = (t_ssl *)in;
	if (!(sha = init_sha256(ssl)))
		return ;
	i = 0;
	while (i < ssl->input_len)
	{
		sha->p += i;
		ft_memset(sha->w, 0x00, CHUNK_SIZE);
		do_algo_sha256(sha);
		i += CHUNK_SIZE;
	}
	i = -1;
	ft_memcpy(sha->str, sha->hash, 32);
	while (++i < 32)
	{
		sha->print = ft_itoa_base(sha->str[i], 16);
		ssl->output = ft_strcat(ssl->output, sha->print);
		ft_strdel(&sha->print);
	}
	free(sha);
}
