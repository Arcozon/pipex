/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:36:36 by geudes            #+#    #+#             */
/*   Updated: 2023/01/14 14:52:01 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	calcsize(char*str, char c)
{
	int	nbword;
	int	i;
	int	i2;

	i = 0;
	nbword = 0;
	while (str[i])
	{
		while (str[i] && c == str[i])
			i++;
		i2 = i;
		while (str[i] && c != str[i])
			i++;
		if (i > i2)
			nbword++;
	}
	return (nbword);
}

static char	*ft_getword(int *is, char *str, char c)
{
	unsigned int	len;
	char			*ptr;

	len = 0;
	ptr = 0;
	while (str[*is + len] && c != str[*is + len])
		len++;
	if (len > 0)
		ptr = ft_substr(str, *is, len);
	while (str[*is + len] && c == str[*is + len])
		(*is)++;
	*is += len;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (0);
	i = -1;
	while (++i < len && ((s + start)[i]))
		str[i] = (s + start)[i];
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tabstr;
	int		is;
	int		nbword;

	if (!s)
		return (0);
	is = 0;
	nbword = 0;
	tabstr = malloc(sizeof (char *) * (calcsize((char *)s, c) + 1));
	if (tabstr == 0)
		return (0);
	while (s[is] && c == s[is])
		is++;
	while (s[is])
	{
		tabstr[nbword] = ft_getword(&is, (char *)s, c);
		if (tabstr[nbword] == 0)
		{
			while (nbword >= 0)
				free(tabstr[nbword--]);
			return (free(tabstr), (char **)0);
		}
		nbword++;
	}
	return (tabstr[nbword] = 0, tabstr);
}
