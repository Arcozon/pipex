/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:40:12 by geudes            #+#    #+#             */
/*   Updated: 2023/01/17 17:25:36 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_exec(char **path, char *cmd)
{
	char	*actual_path;
	char	*buffer;
	int		i;

	i = -1;
	while (path[++i])
	{
		buffer = ft_strjoin("/", cmd);
		actual_path = ft_strjoin(path[i], buffer);
		free(buffer);
		if (!access(actual_path, F_OK))
			return (actual_path);
		free(actual_path);
	}
	return (cmd);
}

char	**get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
			return (ft_split(env[i] + 5, ':'));
	}
	return (0);
}
