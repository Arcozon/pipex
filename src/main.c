/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/01/20 20:14:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_that_fork(char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (fork == -1)
		(printf("Fork error\n"), exit(0));
	if (pid)
	{
		waitpid(pid, 0, 0);
		return ;
	}
	i_gotta_exec_or_not()
}

void	i_gotta_exec_or_not(char *actual_path, char **cmd, char **env
	, pid_t pid)
{
	execve(actual_path, cmd, env);
	write(1, "Oupsi\n", 6);
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	char	**cmd;
	char	*actual_path;

	if (ac < 5)
		return (write(1, "I NEED MORE\n", 12), 0);
	path = get_path(env);
	cmd = ft_split(av[1], ' ');
	actual_path = get_exec(path, cmd[0]);0
	printf("%s\n", actual_path);
	i_gotta_exec_or_not(actual_path, cmd, env, fork());
	write(1, "Oupsi\n", 6);
	return (0);
}
