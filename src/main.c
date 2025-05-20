/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/20 11:37:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 0 on error 1 on succ
void	close_fd(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

int	open_fd(char *f_name, int *fd, int mode, t_px *px)
{
	if (*fd >= 0)
		close(*fd);
	*fd = open(f_name, mode, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
	if (*fd < 0)
	{
		px->errors |= E_OPEN;
		err_file(f_name, px->p_name);
	}
	return (*fd >= 0);
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
		open_fd(px->infile, &(px->ifd), O_RDONLY, px);
	open_fd(px->outfile, &(px->ofd), O_WRONLY | O_CREAT
			| (int [2]){O_TRUNC, O_APPEND}[px->heredoc], px);
}

void	exec_pipex(t_px *px)
{
	open_files(px);
	find_exe_cmds(px->cmds, px->path, px->p_name);
	exec_cmds(px);
	wait_childs(px);
}

int	main(int ac, char *av[], char *env[])
{
	t_px	ppx;

	if (!init_pipex(&ppx, ac, av, env))
		exec_pipex(&ppx);
	free_px(&ppx);
	print_errors(ppx.errors, ppx.p_name);
	return (ppx.r_value);
}
