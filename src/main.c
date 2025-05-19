/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/19 08:14:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 0 on error 1 on succ
int	open_fd(char *f_name, int *fd, int mode, t_px *px)
{
	if (*fd >= 0)
		close(*fd);
	*fd = open(f_name, mode);
	if (fd <= 0)
	{
		px->errors |= E_OPEN;
		err_file(px->p_name, f_name);
	}
	return (fd >= 0);
}

void	open_files(t_px *px)
{
	if (px->heredoc)
	{
		px->ifd = heredoc(px->infile, px->p_name, px->env);
		if (px->infile < 0)
			px->errors |= E_HRDC;
	}
	else
	{
		px->ifd = open(px->infile, O_RDONLY);
		if (px->ifd < 0)
		{
			px->errors |= E_OPEN;
			err_file(px->infile, px->p_name);
		}
	}
	px->ofd = open(px->outfile, O_WRONLY); // append for heredoxc mod
	if (px->ifd < 0)
	{
		px->errors |= E_OPEN;
		err_file(px->outfile, px->p_name);
	}
}

void	exec_pipex(t_px *px)
{
	open_files(px);
}

int	main(int ac, char *av[], char *env[])
{
	t_px	ppx;

	if (!init_pipex(&ppx, ac, av, env))
		exec_pipex(&ppx);
	if (ppx.errors)
	{
		// print_errors(ppx.errors);
		return (ppx.errors);
	}
	return (0);
}
