/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/01/22 02:52:11 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	CLOSE_THEM_ALL(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_cmd - 1)
		(close(pipex->pipes[i][0]), close(pipex->pipes[i][1]));
}

void	I_m_a_fork(char *b_cmd, t_pipex *pipex, char **env)
{
	char	**cmd;
	char	*actual_path;

	cmd = ft_split(b_cmd, ' ');
	actual_path = get_exec(pipex->path, cmd[0]);
	write(1, b_cmd, strlen(b_cmd));
	dup2(pipex->input, 0);
	dup2(pipex->output, 1);
	CLOSE_THEM_ALL(pipex);
	execve(actual_path, cmd, env);
	(free(actual_path), free_split(cmd));
	write(2, "AGH", 3);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_pipex	*pipex;

	if (ac < 4)
		return (printf("More arg pls\n"), 0);
	pipex = init_pipex(ac - 3, av, env);
	i = -1;
	while (++i < pipex->nb_cmd)
	{
		printf("<%d>\n", i);
		if (i)
			pipex->input = pipex->pipes[i - 1][0];
		else
			pipex->input = pipex->infile;
		if (i < pipex->nb_cmd - 1)
			pipex->output = pipex->pipes[i][1];
		else
			pipex->output = pipex->outfile;
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			return (printf("Fork error\n"), 0);
		if (pipex->pids[i])
			I_m_a_fork(av[i + 2], pipex, env);
	}
	waitpid(-1, 0, 0);
	free_pipex(pipex->nb_cmd - 1, pipex);
	return (0);
}
