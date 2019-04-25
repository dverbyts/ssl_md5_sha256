/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:24:08 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 22:24:10 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include <fcntl.h>
# include "libft/libft.h"
# include "sha256.h"
# include "md5.h"

/*
** ••• bool flag format: •••
** • -f_str - string exist
** • -f_p, flag p - echo STDIN to STDOUT and append the checksum to STDOUT
** • -f_q, flag q - quiet mode
** • -f_r, flag r - reverse the format of the output
** • -f_s, flag s - print the sum of the given string
*/

typedef	struct	s_ssl
{
	int		f_str;
	int		f_p;
	int		f_q;
	int		f_r;
	int		f_s;
	int		input_len;
	int		l;
	void	(*wich_algo)(t_ssl *ssl);
	char	*algo_name;
	char	*input;
	char	*output;


	void	*ssl_struct;
	void	*(*ssl_init)(char *input, size_t len);
	void	(*ssl_func)(void *ssl);
	char	*file_name;
	char	*func_name;
}				t_ssl;

int	parsing_input(int algo, int argc, char **argv, t_ssl *ssl);
int	parsing_flag(t_ssl *ssl, char *flag)

#endif