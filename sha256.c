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
	sha->p = (unsigned char *)ft_strnew(ssl->input_len + 64);
	ft_memcpy(sha->p, ssl->input, sha->len);
	sha->p[sha->len] = 128;
	sha->len *= 8;
	ft_memcpy(&sha->p[ssl->input_len], &sha->len, 4);
	sha->len = ft_strlen(ssl->input);
	return (sha);
}
void	calc_chunk(t_sha256 *sha)
{
	size_t space_in_chunk;

	if (sha->total_len_delivered)
		return (0);
	if (sha->len >= CHUNK_SIZE)
	{
		ft_memcpy(sha->chunk, sha)
	}
}


void	ft_sha256(void *in)
{
	t_sha256	*sha;
	t_ssl		*ssl;

	ssl = (t_ssl *)in;
	if (!(sha = init_sha(ssl)))
		return ;
	while (calc_chunk(sha)) //(uint8_t chunk[64], struct buffer_state state)
	{

	}



	print_sha(sha, ssl);
	free(sha);
}




