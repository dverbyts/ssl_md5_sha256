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

#ifndef SSL_H
# define SSL_H
# include <fcntl.h>
# include <stdint.h>
# include "libft/libft.h"
//# include "sha256.h"
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
	size_t	input_len;
	int		l;
	void	(*run_algo)(void *ssl);
	char	*algo_name;
	char	*file_name;
	char	*input;
	char	*output;
}				t_ssl;

int		parsing_input(int argc, char **argv, t_ssl *ssl);
void	ft_md5(void *in);
void	ft_sha256(void *in);
int		ft_error(int ft_error_code, char *msg);

#endif