/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:18:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/20 10:39:16 by gaeudes          ###   ########.fr       */
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

int	check_nb_args(int ac, char *av[])
{
	if (!PPX_BONUS)
		return (ac == 5);
	if (ac < 5)
		return (0);
	if (!ft_strncmp(av[1], HEREDOC,  HEREDOC_LEN) && ac < 6)
		return (0);
	return (1);
}

// 0 on success
int	init_pipex(t_px *ppx,int ac,char *av[],char *env[])
{
	ppx->errors = 0;
	ppx->r_value = 0;
	ppx->last_in = -1;
	ppx->ifd = -1;
	ppx->ofd = -1;
	ppx->outfile = av[ac - 1];
	ppx->env = env;
	ppx->heredoc = 0;
	ppx->p_name = av[0];
	if (slashchr(av[0]))
		ppx->p_name = ft_strrchr(av[0], '/') + 1;
	ppx->path = find_path(env);
	ppx->cmds = 0;
	if (!check_nb_args(ac, av))
		return (ppx->errors |= E_ARGS, 1);
	if (PPX_BONUS)
		ppx->heredoc = (ft_strncmp(av[1], HEREDOC,  HEREDOC_LEN) == 0);
	ppx->infile = av[1 + ppx->heredoc];
	ppx->cmds = init_cmds(av + 2 + ppx->heredoc, ac - 3 - ppx->heredoc, ppx);
	if (!ppx->cmds)
		return (ppx->errors |= E_MLLC, 1);
	return (0);
}
