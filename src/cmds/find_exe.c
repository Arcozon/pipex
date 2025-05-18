/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:48:54 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/18 15:12:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_exe(char *exe_name, char *path)
{
	char	*res;
	size_t	start;
	size_t	len;

	if (!path || slashchr(exe_name))
	{
		if (!access(exe_name ,F_OK))
			return (ft_strdup(exe_name));
		// No suck file or directory
		return (0);
	}
	start = 0;
	while (path[start])
	{
		len = 0;
		while (path[start + len] && path[start + len] != ':')
			++len;
		res = ft_substrjoin_with_slash(exe_name, path, start, len);
		if (!res || !access(res, F_OK))
			return (res);
		free(res);
		start += len;
		if (path[start])
			++start;
	}
	// command not found
	return (0);
}
