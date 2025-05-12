/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:18:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 12:04:27 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// 0 on success
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
	ppx->cmds = init_cmds(av + 2 + ppx->heredoc, ac - 3 - ppx->heredoc, env, ppx->path);
	if (!ppx->cmds)
		return (ppx->errors |= F_MLLC, 1);
	return (0);
}
