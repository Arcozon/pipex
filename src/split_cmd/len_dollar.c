/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:45:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 16:09:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_var_name(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

size_t	len_var_name(char *str)
{
	size_t	len;

	len = 0;
	while (is_var_name(str[len]))
		++len;
	return (len);
}

size_t	len_dollar(char	*str, size_t *i, char **env)
{
	size_t	len_vname;
	size_t	len_vcontent;

	++*i;
	len_vname = len_var_name(str + *i);
	if (!len_vname)
		return (1);
	len_vcontent = 0;
	if (env)
	{
		while (*env)
		{
			if (!ft_strncmp_weq(str + *i, *env, len_vname))
			{
				len_vcontent = ft_strlen(*env + len_vname + 1);
				break ;
			}
			++ env;
		}
	}
	*i += len_vname;
	return (len_vcontent);
}
