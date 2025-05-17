/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:45:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 16:37:34 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	len_var_name(char *str)
{
	size_t	len;

	len = 0;
	if (str[len] >= '0' && str[len] <= '9')
		return (1);
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
