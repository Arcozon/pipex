/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:21:28 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/19 13:36:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp_weq(char *name, char *env_var, size_t n)
{
	while (n && *name)
	{
		if (*name != *env_var)
			return (1);
		--n;
		++name;
		++env_var;
	}
	if (!n && *env_var == '=')
		return (0);
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

int	slashchr(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		++str;
	}
	return (0);
}

char	*ft_strrchr(char *str, char c)
{
	size_t	i;

	i = ft_strlen(str);
	if (!c)
		return (str + i);
	while (i--)
		if (str[i] == c)
			return (str + i);
	return (0);
}

char	*ft_substrjoin_with_slash(char *path, char *exe,
		size_t start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	j = ft_strlen(path);
	if (start > j)
		start = j;
	if (start + len > j)
		len = j - start ;
	res = malloc((ft_strlen(exe) + len + 1 + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = path[i];
		++i;
	}
	res[i++] = '/';
	j = 0;
	while (exe[j])
	{
		res[i + j] = exe[j];
		++j;
	}
	res[i + j] = '\0';
	return (res);
}
