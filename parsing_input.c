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

int	parsing_flag(t_ssl *ssl, char *flag)
{
	if (ft_strcmp(flag, "-p") == 0)
		ssl->f_p == 1 ? error(3, flag) : ssl->f_p = 1;
	else if (ft_strcmp(flag, "-q") == 0)
		ssl->f_q == 1 ? error(3, flag) : ssl->f_q = 1;
	else if (ft_strcmp(flag, "-r") == 0)
		ssl->f_r == 1 ? error(3, flag) : ssl->f_r = 1;
	else if (ft_strcmp(flag, "-s") == 0)
		ssl->f_s == 1 ? error(3, flag) : ssl->f_s = 1;
	else
	{
		error(2, flag);
		return (1);
	}
	return (0);
}

int	parsing_input(int algo, int argc, char **argv, t_ssl *ssl)
{
	int i;
	int error;

	i = 2;
	error = 1;
	while (++i < argc)
	{
		error = 0;
		if (argv[i][0] == "-")
			error = parsing_flag(ssl, argv[i]);
		else if (ssl->f_str == 0)
		{
			ssl->input = argv[i];
			ssl->f_str = 1;
		}
		else
			return (error(2, argv[i]));
		if (error != 0)
			return (1);
	}
	do_some_ssl(); /*to do - check if input exist and run hashing algo*/
	return (error);
}
