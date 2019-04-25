/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:09:49 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 21:10:35 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

t_ssl	init_struct(int algo)
{
	t_ssl	*ssl;

	ssl = (t_ssl *)malloc(sizeof(t_ssl));
	ssl->f_str = 0;
	ssl->f_p = 0;
	ssl->f_q = 0;
	ssl->f_r = 0;
	ssl->f_s = 0;
	ssl->l = 1;
	ssl->input = NULL;
	ssl->output = NULL;
	if (algo == 1)
	{
		ssl->algo_name = "MD5";
		ssl->wich_algo = &ft_md5;
	}
	else if (algo == 2)
	{
		ssl->algo_name = "SHA256";
		ssl->wich_algo = &ft_sha256;
	}
	return (ssl);
}

/*
** known algorithms is:
** 0 - NA
** 1 - md5
** 2 - sha256
*/

int		find_algo(char *str)
{
	int		re;

	re = 0;
	if (ft_strcmp(argv[1], "md5") == 0)
		re = 1;
	if (ft_strcmp(argv[1], "sha256") == 0)
		re = 2;
	return (re);
}

/*
** error_code:
** 1 - print usage and exit
** 2 - error, print mesage and exit
** 3 - warning, print mesage, continue
*/

int		error(int error_code, char *msg)
{
	if (error_code == 1)
		ft_putstr("\nUsage: ssl [md5 sha256 ...] [-p ...] [string]\n-p
			- echo STDIN to STDOUT and append the checksum to STDOUT\n -q
			- quiet mode\n -r - reverse the format of the output\n -s
			- print the sum of the given string\n");
	else if (error_code == 2)
	{
		ft_putstr("\nERROR\nWrong input or undefined behavior. Reason:\n");
		ft_putstr(msg);
		ft_putstr("\n");
	}
	else if (error_code == 3)
	{
		ft_putstr("\nWARNING\nsome problem with\n");
		ft_putstr(msg);
		ft_putstr("\n");
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int		algo;
	t_ssl	*ssl;

	algo = 0;
	if (argc < 2 || argc < 3)
		return (error(1, NULL));
	algo = find_algo(argv[1]);
	if (algo == 0)
		return (error(1, NULL));
	ssl = init_struct(algo);
	if (parsing_input(algo, argc, argv, ssl) != 0)
	{
		if (ssl)
			free(ssl);
		return (error(1, NULL));
	}
	
	ft_putstr(ssl->output);
	if (ssl)
		free(ssl);
	return (0);
}
