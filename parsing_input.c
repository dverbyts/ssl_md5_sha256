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

void	parsing_flag(t_ssl *ssl, int argc, char **argv, int i)
{
	while (argv[ssl->l][++i])
	{
		if (ft_strcmp(argv[ssl->l][i], "p") == 0)
			ssl->f_p == 1 ? error(3, argv[ssl->l]) : ssl->f_p = 1;
		else if (ft_strcmp(argv[ssl->l][i], "q") == 0)
			ssl->f_q == 1 ? error(3, argv[ssl->l]) : ssl->f_q = 1;
		else if (ft_strcmp(argv[ssl->l][i], "r") == 0)
			ssl->f_r == 1 ? error(3, argv[ssl->l]) : ssl->f_r = 1;
		else if (ft_strcmp(argv[ssl->l][i], "s") == 0)
		{
			ssl->f_r == 1 ? error(3, argv[ssl->l]) : ssl->f_r = 1;
			if (argv[ssl->l][i + 1] == "\0")
				(ssl->l < (argc - 1)) ? ssl->input = argv[++ssl->l] : 
										ssl->input = "";
			else
				ssl->input = &argv[ssl->l][i + 1];
			ssl->f_str = 1;
			return ;
		}
		else
			error(3, argv[ssl->l]);
	}
}

int		parsing_input(int algo, int argc, char **argv, t_ssl *ssl)
{
	while (++ssl->l < argc)
	{
		if (argv[ssl->l][0] == "-")
			parsing_flag(ssl, argc, argv, 0);
		else
		{
			ssl->input = argv[ssl->l];
			ssl->f_str = 1;
		}		
		if (ssl->f_str == 1) // to do - if no -s flag, and some file exist, I need to parse file and ssl him.
		{
			do_some_ssl();
			print_ssl();
			ssl->f_str = 0;
		}	
	}
	return (0);
}

