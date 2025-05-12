/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:07:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 16:26:46 by gaeudes          ###   ########.fr       */
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
	size_t	i;

	if (!cmd)
		return ;
	free(cmd->path);
	free(cmd);
}

t_cmd	*empty_new_cmd(char *pre_split)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->pre_split = pre_split;
	new->ifd = -1;
	new->ofd = -1;
	new->args = 0;
	new->path = 0;
	new->pid = -1;
	new->next = 0;
	return (new);
}

t_cmd	*new_cmd(char *pre_split, char **env, char *path)
{
	t_cmd	*new;

	new = empty_new_lst(pre_split);
	if (!new)
		return (0);
	// new->args = 
}

t_cmd	*init_cmds(char	**av, size_t nb_cmds, char **env, char *path)
{
	size_t	i;
	t_cmd	*lst;
	t_cmd	*new;

	lst = 0;
	i = 0;
	while (i < nb_cmds)
	{
		new = new_cmd(av[i], env, path);
		++i;
	}
}
