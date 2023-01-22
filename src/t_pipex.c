/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipex->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:34:51 by geudes            #+#    #+#             */
/*   Updated: 2023/01/22 00:18:09 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(int nb_pipes, t_pipex *pipex)
{
	while (--nb_pipes >= 0)
		(close(pipex->pipes[nb_pipes][0]), close(pipex->pipes[nb_pipes][1]),
				free(pipex->pipes[nb_pipes]));
	free_split(pipex->path);
	if (pipex->infile)
		close(pipex->infile);
	if (pipex->outfile)
		close(pipex->outfile);
	(free(pipex->pids), free(pipex->pipes), free(pipex));
}

t_pipex	*init_pipex(int nb_cmd, char **av, char **env)
{
	t_pipex *pipex;
	int i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		(printf("Malloc error"), exit(0));
	pipex->pids = malloc(sizeof(pid_t) * nb_cmd);
	if (!pipex->pids)
		(printf("Malloc error"), free(pipex), exit(0));
	pipex->pipes = malloc(sizeof(int *) * (nb_cmd - 1));
	if (!pipex->pipes)
		(printf("Malloc error"), free(pipex->pids), free(pipex), exit(0));
	pipex->infile = open(av[1], O_RDONLY);
	pipex->outfile = open(av[nb_cmd + 2], O_TRUNC | O_CREAT | O_RDWR, 0644);
	pipex->path = get_path(env);
	i = -1;
	while (++i < nb_cmd - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
			(printf("Pipes error"), free_pipex(i, pipex), exit(0));
	}
	pipex->nb_cmd = nb_cmd;
	return (pipex);
}