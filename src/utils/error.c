/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:07:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/19 12:17:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	putstrerr(char *err)
{
	write(2, err, ft_strlen(err));
}

void	err_expected_delim(char *limiter, char *p_name, int to_print)
{
	if (!to_print)
		return ;
	putstrerr("\n");
	putstrerr(p_name);
	putstrerr(" :warning: here-document delimited by end-of-file (wanted '");
	putstrerr(limiter);
	putstrerr("')\n");
}

void	err_file(char *f_name, char *p_name)
{
	putstrerr(p_name);
	putstrerr(": ");
	perror(f_name);
}

void	px_error(char *p_name, char *error)
{
	putstrerr(p_name);
	putstrerr(": ");
	putstrerr(error);
	putstrerr("\n");
}

void	print_errors(unsigned char errors, char *p_name)
{
	if (errors & E_ARGS)
		px_error(p_name, "Wrong argument format");
	if (errors & E_MLLC)
		px_error(p_name, "Malloc error");
	if (errors & E_HRDC)
		px_error(p_name, "Heredoc error (Malloc or pipe, shouldnt be read/write)");
	if (errors & E_FORK)
		px_error(p_name, "Fork error");
}
