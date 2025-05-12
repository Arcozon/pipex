/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:21:28 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 15:25:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp_weq(char *name, char *var, size_t n)
{
	while (n && *name)
	{
		if (*name != *var)
			return (1);
		--n;
		++name;
		++var;
	}
	if (!n && *var == '=')
		return (0);
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while(str[len])
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

char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1 + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		++i;
	}
	res[i++] = '/';
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		++j;
	}
	res[i + j] = '\0';
	return (res);
}
