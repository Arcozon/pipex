/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:37:53 by geudes            #+#    #+#             */
/*   Updated: 2023/01/21 00:53:02 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

unsigned int	ft_strlen(const char *caca)
{
	int	i;

	i = 0;
	if (!caca)
		return (-1);
	while (caca[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		iptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	iptr = 0;
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[i])
		ptr[iptr++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[iptr++] = s2[i++];
	ptr[iptr] = '\0';
	return (ptr);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split && split[++i])
		free(split[i]);
	free(split);
}
