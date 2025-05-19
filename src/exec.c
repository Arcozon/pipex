/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:08:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/19 12:22:04 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	files_cmd(t_cmd *cmd, t_px *px)
{
	int	pipes[2];

	if (cmd == px->cmds)
	{
		cmd->infd = px->ifd;
		px->ifd = -1;
	}
	else
		cmd->infd = px->last_in;
	px->last_in = -1;
	if (cmd->next)
	{
		if (pipe(pipes) < 0)
			return (px->errors |= E_PIPE, 0);
		cmd->outfd = pipes[1];
		px->last_in = pipes[0];
	}
	else
	{
		cmd->outfd = px->ofd;
		close_fd(&(px->ofd));
	}
	return (1);
}

void	make_a_child(t_cmd *cmd, t_px *px)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		px->errors |= E_FORK;
	if (cmd->pid != 0)
		return ;
	if (dup2(cmd->infd, STDIN_FILENO) >= 0 || dup2(cmd->outfd, STDOUT_FILENO) >= 0)
	{
		close_fd(&(cmd->infd));
		close_fd(&(cmd->outfd));
		execve(cmd->path, cmd->args, px->env);
		err_file(cmd->path, px->p_name);
	}
	free_px(px);
	exit(E_EXEC);
}

void	exec_cmds(t_px* px)
{
	t_cmd	*cmd;

	cmd = px->cmds;
	while (cmd)
	{
		if (!files_cmd(cmd, px))
			return ;
		if (cmd->outfd != -1 && cmd->infd != -1 && cmd->path)
			make_a_child(cmd, px);
		close_fd(&(cmd->infd));
		close_fd(&(cmd->outfd));
		cmd = cmd->next;
	}
}
