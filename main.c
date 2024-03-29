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

t_ssl	*init_struct(int algo)
{
	t_ssl	*ssl;

	if (!(ssl = (t_ssl *)malloc(sizeof(t_ssl))))
	{
		ft_er(2, "Malloc error. Sustem dom't give memory");
		return (NULL);
	}
	ft_bzero(ssl, (sizeof(t_ssl)));
	ssl->output = ft_strnew(2000);
	ssl->l = 1;
	ssl->input = NULL;
	if (algo == 1)
	{
		ssl->algo_name = "MD5";
		ssl->run_algo = &ft_md5;
	}
	else if (algo == 2)
	{
		ssl->algo_name = "SHA256";
		ssl->run_algo = &ft_sha256;
	}
	return (ssl);
}

/*
** known algorithms is:
** 0 - NA
** 1 - md5
** 2 - sha256
*/

int		find_algo(const char *argv)
{
	int		re;

	re = 0;
	if (ft_strcmp(argv, "md5") == 0)
		re = 1;
	if (ft_strcmp(argv, "sha256") == 0)
		re = 2;
	return (re);
}

/*
** error_code:
** 1 - print usage and exit
** 2 - error, print mesage and exit
** 3 - warning, print mesage, continue
** 4 - print mesage in ""
*/

int		ft_er(int ft_er_code, char *msg)
{
	if (ft_er_code == 1)
		ft_putstr("\nUsage: ssl [md5 sha256 ...] [-p ...] [string]\n-p\
			- echo STDIN to STDOUT and append the checksum to STDOUT\n-q\
			- quiet mode\n-r\
			- reverse the format of the output\n-s\
			- print the sum of the given string\n");
	else if (ft_er_code == 2)
	{
		ft_putstr("\nERROR\nWrong input or undefined behavior. Reason:\n");
		ft_putstr(msg);
		ft_putstr("\n");
	}
	else if (ft_er_code == 4)
	{
		ft_putstr("\nWARNING\nsome problem with\n");
		ft_putstr(msg);
		ft_putstr("\n");
	}
	return (1);
}

void	p_res(int i, t_ssl *ssl)
{
	if (!ssl->f_r)
	{
		i == 4 ? ft_putstr(" (\"") : ft_putstr(" (");
		ssl->f_s == 1 ? ft_putstr(ssl->input) : ft_putstr(ssl->file_name);
		i == 4 ? ft_putstr("\") = ") : ft_putstr(") = ");
	}
	else
	{
		i == 4 ? ft_putstr(" (\"") : ft_putstr(" (");
		ssl->f_s == 1 ? ft_putstr(ssl->input) : ft_putstr(ssl->file_name);
		i == 4 ? ft_putstr("\") ") : ft_putstr(") ");
	}
}

int		main(int argc, char **argv)
{
	int		algo;
	t_ssl	*ssl;

	if (argc < 2)
		return (ft_er(1, NULL));
	algo = find_algo(argv[1]);
	if (algo == 0)
		return (ft_er(1, NULL));
	ssl = init_struct(algo);
	parsing_input(argc, argv, ssl);
	if (!ssl->f_fack)
	{
		ssl->run = 69;
		ssl->f_str = 1;
		ssl->input = "";
		ssl->l = 0;
		parsing_input(argc, argv, ssl);
	}
	return (0);
}
