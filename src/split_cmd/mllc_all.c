/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mllc_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 19:12:59 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**mllc_all(char *str, char **env)
{
	char	**args;
	size_t	i;
	size_t	i_arg;

	args = malloc(sizeof(char *) * (count_args(str, env) + 1));
	if (args)
	{
		i = 0;
		i_arg = 0;
		while (is_cmd_sep(str[i]))
				++i;
		while (str[i])
		{
			args[i_arg] = malloc(sizeof(char)
					* (len_one_arg(str, &i, env) + 1));
			if (!args[i_arg])
				return (free_split(args), (char **)0);
			while (is_cmd_sep(str[i]))
				++i;
			i_arg++;
		}
		args[i_arg] = 0;
	}
	return (args);
}

char	**split_cmd(char *str, char **env)
{
	char	**args;
	size_t	i_arg;

	args = mllc_all(str, env);
	if (!args)
		return (0);
	i_arg = 0;
	while (is_cmd_sep(*str))
		++str;
	while (*str)
	{
		cpy_one_arg(args[i_arg], &str, env);
		while (is_cmd_sep(*str))
			++str;
		++i_arg;
	}
	return (args);
}
