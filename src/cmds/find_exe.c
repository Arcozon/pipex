/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:48:54 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 17:18:07 by gaeudes          ###   ########.fr       */
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
		if (!access(exe_name ,X_OK))
			return (ft_strdup(exe_name));
		return (0);
	}
	start = 0;
	while (path[start])
	{
		len = 0;
		while (path[start + len] && path[start + len] != ':')
			++len;
		res = ft_substrjoin_with_slash(exe_name, path, start, len);
		if (!res || !access(res, X_OK))
			return (res);
		free(res);
		start += len;
		if (path[start])
			++start;
	}
	return (0);
}
