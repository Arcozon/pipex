/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:18:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/09 16:28:44 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*find_path(char **env)
{
	if (!env)
		return (0);
	while (*env)
	{
		if (!ft_strncmp(*env, PATH_EQ, PATH_EQ_LEN))
			return (*env + PATH_EQ_LEN);
		++env;
	}
	return (0);
}

int	init_pipex(t_px *ppx,int ac,char *av[],char *env[])
{
	ppx->errors = 0;
	if (ac < 5)
		return (ppx->errors |= F_ARGS, 1);
	ppx->av_0 = av[0];
	ppx->heredoc = 0;
	if (PPX_BONUS)
		ppx->heredoc = ft_strncmp(av[1], HEREDOC,  HEREDOC_LEN) == 0;
	ppx->infile = av[1 + ppx->heredoc];
	ppx->outfile = av[ac - 1];
	ppx->path = find_path(env);
	ppx->nb_cmds = ac - 3 - ppx->heredoc;
	ppx-cmds = init_cmds(av + 2 + ppx->heredoc, ppx->nb_cmds, env);
	if (!ppx->cmds)
		return (ppc->errors |= F_MLLC, 1);
	return (0);
}