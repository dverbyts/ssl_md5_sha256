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

void	print_algo_name(t_ssl *ssl)
{
	ssl->f_fack = 1;
	ssl->run = 0;
	if (ssl->f_p)
	{
		ssl->f_p = 0;
		return (ft_putstr(ssl->input));
	}
	if (ssl->f_q)
		return ;
	if (!ssl->f_r)
	{
		ft_putstr(ssl->algo_name);
		ssl->f_s == 1 ? p_res(4, ssl) : p_res(5, ssl);
	}
	else
		ssl->f_s == 1 ? p_res(4, ssl) : p_res(5, ssl);
}

void	parsing_read_file(int fd, t_ssl *ssl)
{
	char tmp[2];
	char *buf;
	char *bbuf;

	bbuf = ft_strnew(1);
    ft_bzero(tmp, 2);
	while (read(fd, tmp, 1) > 0)
	{
		buf = bbuf;
		bbuf = ft_strjoin(buf, tmp);
		free(buf);
        ft_bzero(tmp, 2);
	}
	ssl->input = bbuf;
}

int		parsing_open_file(int argc, char **argv, t_ssl *ssl, int fd)
{
	if (fd == 69)
	{
		parsing_read_file(0, ssl);
		ssl->file_name = ssl->input;
		ssl->f_p = 1;
	}
	else if ((fd = open(argv[ssl->l], O_RDONLY)) > 0)
	{
		parsing_read_file(fd, ssl);
		ssl->file_name = argv[ssl->l];
		close(fd);
	}
	else if (ssl->f_s)
		ssl->input = argv[argc - 1];
	else
	{
		ssl->f_n == 0 ? ft_putstr("ft_ssl: ") : ft_putstr("\nft_ssl: ");
		ft_putstr(ssl->algo_name);
		ft_putstr(": ");
		ft_putstr(argv[ssl->l]);
		ft_putstr(": No such file or directory");
		return (1);
	}
	ssl->f_str = 1;
	return (0);
}

void	parsing_flag(t_ssl *ssl, int argc, char **argv, int i)
{
	while (argv[ssl->l][++i])
	{
		if (argv[ssl->l][i] == 'p')
			parsing_open_file(argc, argv, ssl, 69);
		else if (argv[ssl->l][i] == 'q')
			(ssl->f_q == 1) ? (ft_er(3, argv[ssl->l])) : (ssl->f_q = 1);
		else if (argv[ssl->l][i] == 'r')
			(ssl->f_r == 1) ? (ft_er(3, argv[ssl->l])) : (ssl->f_r = 1);
		else if (argv[ssl->l][i] == 's')
		{
			(ssl->f_s == 1) ? (ft_er(3, argv[ssl->l])) : (ssl->f_s = 1);
			if (argv[ssl->l][i + 1] == '\0')
				(ssl->l < (argc - 1)) ? (ssl->input = argv[++ssl->l]) :
				(ssl->input = "");
			else
				ssl->input = &argv[ssl->l][i + 1];
			ssl->f_str = 1;
			return ;
		}
		else
			ssl->input = "";
	}
}

void	parsing_input(int argc, char **argv, t_ssl *ssl)
{
	while (++ssl->l < argc || ssl->run == 69)
	{
		if (argv[ssl->l][0] == '-')
			parsing_flag(ssl, argc, argv, 0);
		else if (ssl->f_s == 1)
		{
			ssl->input = argv[ssl->l];
			ssl->f_str = 1;
		}
		else if (ssl->f_s == 0 && ssl->run != 69)
			parsing_open_file(argc, argv, ssl, 0);
		if (ssl->f_str == 1)
		{
			ssl->run_algo(ssl);
			if (ssl->f_r != 1 || ssl->f_p)
				print_algo_name(ssl);
			ft_putstr(ssl->output);
			ft_bzero(ssl->output, ft_strlen(ssl->output));
			if (ssl->f_r)
				print_algo_name(ssl);
			ft_putstr("\n");
			ssl->f_str = 0;
			ssl->f_s = 0;
		}
	}
}
