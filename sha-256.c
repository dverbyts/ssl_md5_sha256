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

