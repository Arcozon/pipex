/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:07:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/09 17:09:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(t_cmd cmd)
{
	size_t	i;

	if (cmd.av)
	{
		i = 0;
		while (cmd.av[i])
			free(cmd.av[i++]);
		free(cmd.av);
		
	}
	free(cmd.path);
}

t_cmd	*init_cmds(char	**av, size_t nb_cmds, char **env)
{
	(void)env;
	t_cmd	*cmds;
	size_t	i;

	cmds = malloc(sizeof(t_cmd) * nb_cmds);
	if (!cmds)
		return (0);
	i = 0;
	while (i < nb_cmds)
	{
		cmds[i].av_i = av[i];
		cmds[i].ifd = -1;
		cmds[i].ofd = -1;
		cmds[i].pid = -1;
		if (!init_one_cmd(cmds + i, av[i], env))
		{
			while (i)
				free_cmd(cmds[--i]);
			free(cmds);
			return (0);
		}
		++i;
	}
}