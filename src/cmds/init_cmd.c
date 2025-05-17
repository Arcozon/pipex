/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:07:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 17:48:04 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*empty_new_cmd(char *pre_split)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->pre_split = pre_split;
	new->infd = -1;
	new->outfd = -1;
	new->args = 0;
	new->path = 0;
	new->pid = -1;
	new->next = 0;
	return (new);
}

t_cmd	*new_cmd(char *pre_split, char **env, char *path)
{
	t_cmd	*new;

	new = empty_new_cmd(pre_split);
	if (!new)
		return (0);
	new->args = split_cmd(pre_split, env);
	if (!new->args)
		return (free(new), (t_cmd *)0);
	new->path = find_exe(new->args[0], path);
	if (!new->path)
		return (free_cmd(new), (t_cmd *)0);
	return (new);
}

t_cmd	*init_cmds(char	**av, size_t nb_cmds, char **env, char *path)
{
	size_t	i;
	t_cmd	*lst;
	t_cmd	**ptr_to_last;
	t_cmd	*new;

	lst = 0;
	i = 0;
	ptr_to_last = &lst;
	while (i < nb_cmds)
	{
		new = new_cmd(av[i], env, path);
		if (!new)
			return (free_lst_cmd(lst), (t_cmd *)0);
		*ptr_to_last = new;
		ptr_to_last = &(new->next);
		++i;
	}
	return (lst);
}
