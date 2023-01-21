/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/01/21 20:59:44 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	create_that_fork(char *avx, char **env, int input, int output)
{
	pid_t	pid;
	char	**cmd;
	char	*actual_path;

	pid = fork();
	if (pid == -1)
		(printf("Fork error\n"), exit(0));
	if (pid)
		return (pid);
	cmd = ft_split(avx, ' ');
	actual_path = get_exec(env, cmd[0]);
	dup2(output, 1);
	dup2(input, 0);
	execve(actual_path, cmd, env);
	(free(actual_path), free_split(cmd));
	write(1, "Oupsi\n", 6);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	pipes[2];
	int	input;
	int	output;

	if (ac < 5)
		return (write(1, "I NEED MORE\n", 12), 0);
	i = 1;
	while (++i < ac - 1)
	{
		if (pipe(pipes))
			(printf("Error"), exit(0));
		input = pipes[0];
		output = pipes[1];
		if (i == 2)
			input = (close(input), open(av[1], O_RDONLY));
		if (i == 2 && input == -1)
			(printf("Input file error\n"), exit(0));
		if (i == ac - 2)
			output = (close(output), open(av[ac - 1],
						O_TRUNC | O_CREAT | O_RDWR, 0000644));
		waitpid(create_that_fork(av[i], env, input, output), 0, 0);
		printf("Done waiting %s\n", av[i]);
		close(input);
		close(output);
	}
	return (0);
}
