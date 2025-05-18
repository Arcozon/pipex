/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/18 19:00:03 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	px->ofd = open(px->outfile, O_WRONLY);
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
