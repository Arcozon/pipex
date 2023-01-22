/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/01/22 02:34:14 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	I_m_a_fork(char *b_cmd, t_pipex *pipex, char **env, int to_close)
{
	char	**cmd;
	char	*actual_path;

	cmd = ft_split(b_cmd, ' ');
	actual_path = get_exec(pipex->path, cmd[0]);
	write(1, b_cmd, strlen(b_cmd));
	dup2(pipex->input, 0);
	if (to_close)
		close(to_close);
	dup2(pipex->output, 1);
	execve(actual_path, cmd, env);
	(free(actual_path), free_split(cmd));
	write(2, "AGH", 3);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_pipex	*pipex;
	int		to_close;

	if (ac < 4)
		return (printf("More arg pls\n"), 0);
	pipex = init_pipex(ac - 3, av, env);
	i = -1;
	to_close = 0;
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
			I_m_a_fork(av[i + 2], pipex, env, to_close);
		if (i < pipex->nb_cmd - 1)
			to_close = pipex->pipes[i][1];
	}
	i = -1;
	while (++i < pipex->nb_cmd)
	{
		waitpid(pipex->pids[i], 0, 0);
		write(1, "back here\n", 10);
		if (i < pipex->nb_cmd - 1)
			(close(pipex->pipes[i][1]));
	}
	return (0);
}
