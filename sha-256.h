/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha-256.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:41:49 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 16:41:55 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CHUNK_SIZE 64
#define TOTAL_LEN_LEN 8

static const uint32_t g_k[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
		0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,	0xe49b69c1, 0xefbe4786,
		0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
		0x06ca6351, 0x14292967,	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,	0xa2bfe8a1, 0xa81a664b,
		0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
		0x5b9cca4f, 0x682e6ff3,	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

/* g_h[0] - g_h[7] */
uint32_t g_h[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f,
		0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

struct buffer_state {
	const uint8_t * p;
	size_t len;
	size_t total_len;
	int single_one_delivered; /* bool */
	int total_len_delivered; /* bool */
};

struct string_vector {
	char *input;
	char *output;
};

static const struct string_vector STRING_VECTORS[] = {
	{
		"",
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
	},
	{
		"abc",
		"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
	},
	{
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef",
		"a8ae6e6ee929abea3afcfc5258c8ccd6f85273e0d4626d26c7279f3250f77c8e"
	},
	{
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde",
		"057ee79ece0b9a849552ab8d3c335fe9a5f1c46ef5f1d9b190c295728628299c"
	},
	{
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0",
		"2a6ad82f3620d3ebe9d678c812ae12312699d673240d5be8fac0910a70000d93"
	},
	{
		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
		"248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"
	},
	{
		"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
		"ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
		"cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1"
	}
};