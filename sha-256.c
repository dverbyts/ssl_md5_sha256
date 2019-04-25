/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha-256.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:42:14 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 16:42:17 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void init_buf_state(struct buffer_state *state, const void * input, size_t len)
{
	state->p = input;
	state->len = len;
	state->total_len = len;
	state->single_one_delivered = 0;
	state->total_len_delivered = 0;
}

void calc_sha_256(uint8_t hash[32], const char *input, size_t len)
{
	uint8_t chunk[64];
	struct buffer_state state;

	init_buf_state(&state, input, len);
}

int string_test(const char input[], const char output[])
{
	uint8_t hash[32];
	char hash_string[65];

	calc_sha_256(hash, input, ft_strlen(input));



	hash_to_string(hash_string, hash);
	printf("input: %s\n", input);
	printf("hash : %s\n", hash_string);
	if (strcmp(output, hash_string)) {
		printf("FAILURE!\n\n");
		return 1;
	} else {
		printf("SUCCESS!\n\n");
		return 0;
	}		
}




t_md5	init_md5(void)
{
	t_md5 *md5;

	if (!(md5 = (t_md5 *)malloc(sizeof(t_md5))))
	{
		error(2, "Malloc error. Sustem dom't give memory");
		return (NULL);
	}
	md5->a = 0x67452301;
	md5->b = 0xefcdab89;
	md5->c = 0x98badcfe;
	md5->d = 0x10325476;
	md5->aa = 0;
	md5->bb = 0;
	md5->cc = 0;
	md5->dd = 0;
}

void	ft_sha256(t_ssl *ssl)
{
	uint32_t	buf;
	int			move;
	t_md5		*md5;

	move = 0;
	if (!(md5 = init_md5()))
		return ;
	while (ssl->input_len > move)
	{
		buf = (uint32_t *)(ssl->input + move);
		md5->aa = md5->a;
		md5->bb = md5->b;
		md5->cc = md5->c;
		md5->dd = md5->d;
		do_algo(buf, md5, 0, 0);
		md5->a += md5->aa;
		md5->b += md5->bb;
		md5->c += md5->cc;
		md5->d += md5->dd;
		move += 64;
	}
	print_md5(md5, ssl);
	if (md5)
		free(md5);
	return ;
}