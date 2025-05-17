/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:37:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 17:45:24 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_var_name(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_strdup(char *str)
{
	char	*res;
	size_t	i;

	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		++i;
	}
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
