/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:48:54 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/20 11:58:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_exe(char *exe_name, char *path, char *p_name)
{
	char	*res;
	size_t	start;
	size_t	len;

	if (!path || slashchr(exe_name))
	{
		if (!access(exe_name, F_OK))
			return (ft_strdup(exe_name));
		return (err_file(exe_name, p_name), (char *)0);
	}
	start = 0;
	while (path[start])
	{
		len = 0;
		while (path[start + len] && path[start + len] != ':')
			++len;
		res = ft_substrjoin_with_slash(path + start, exe_name, len);
		if (!res || !access(res, F_OK))
			return (res);
		free(res);
		start += len;
		if (path[start])
			++start;
	}
	return (err_cmd_not_found(p_name, exe_name), (char *)0);
}
