/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:18:59 by dverbyts          #+#    #+#             */
/*   Updated: 2019/04/23 21:19:01 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	parsing_read_file(int fd, t_ssl *ssl)
{
	char tmp[100];
	char *buf;

	while (read(fd, tmp, 100) > 0)
	{
		if (ssl->input == NULL)
			ssl->input = ft_strnew(0);
		buf = ssl->input;
		ssl->input = ft_strjoin(buf, tmp);
		free(buf);
	}
}

int		parsing_open_file(int argc, char **argv, t_ssl *ssl, int fd)
{
	if (ssl->l == (argc - 1))
	{
		ssl->input = "";
		ssl->f_str = 1;
		return (0);
	}
	if ((fd = open(argv[ssl->l], O_RDONLY)) < 0)
		return (ft_error(2, "File name error. Can't find file."));
	if (fd > 0)
	{
		parsing_read_file(fd, ssl);
		ssl->file_name = argv[ssl->l];
		ssl->f_str = 1;
		close(fd);
		return (0);
	}
	ssl->input = "";
	ssl->f_str = 1;
	return (0);
}

void	parsing_flag(t_ssl *ssl, int argc, char **argv, int i)
{
	while (argv[ssl->l][++i])
	{
		if (argv[ssl->l][i] == 'p')
			(ssl->f_p == 1) ? (ft_error(3, argv[ssl->l])) : (ssl->f_p = 1);
		else if (argv[ssl->l][i] == 'q')
			(ssl->f_q == 1) ? (ft_error(3, argv[ssl->l])) : (ssl->f_q = 1);
		else if (argv[ssl->l][i] == 'r')
			(ssl->f_r == 1) ? (ft_error(3, argv[ssl->l])) : (ssl->f_r = 1);
		else if (argv[ssl->l][i] == 's')
		{
			(ssl->f_s == 1) ? (ft_error(3, argv[ssl->l])) : (ssl->f_s = 1);
			if (argv[ssl->l][i + 1] == '\0')
				(ssl->l < (argc - 1)) ? (ssl->input = argv[++ssl->l]) :
				(ssl->input = "");
			else
				ssl->input = &argv[ssl->l][i + 1];
			ssl->f_str = 1;
			return ;
		}
		else
			ft_error(3, argv[ssl->l]);
	}
}

int		parsing_input(int argc, char **argv, t_ssl *ssl)
{
	while (++ssl->l < argc)
	{
		if (argv[ssl->l][0] == '-')
			parsing_flag(ssl, argc, argv, 0);
		else if (ssl->f_s == 1)
		{
			ssl->input = argv[ssl->l];
			ssl->f_str = 1;
			ssl->f_s = 0;
		}
		else if (ssl->f_s == 0)
			parsing_open_file(argc, argv, ssl, 0);
		if (ssl->f_str == 1)
		{
//			if (ssl->f_r != 1)
//				print_algo_name(ssl);
			ssl->run_algo(ssl);
//			print_ssl();
//			if (ssl->f_r == 1)
//				print_algo_name(ssl);
			ssl->f_str = 0;
		}
	}
	return (0);
}
