/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:47:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/19 12:20:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);	
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	close_fd(&(cmd->infd));
	close_fd(&(cmd->outfd));
	free_split(cmd->args);
	free(cmd->path);
	free(cmd);
}

void	free_lst_cmd(t_cmd *lst)
{
	t_cmd	*to_free;

	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free_cmd(to_free);
	}
}

void	free_px(t_px *px)
{
	close_fd(&(px->last_in));
	close_fd(&(px->ofd));
	close_fd(&(px->ifd));
	free_lst_cmd(px->cmds);
}
