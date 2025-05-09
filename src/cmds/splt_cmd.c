/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splt_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:10:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/09 17:51:59 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_cmd_sep(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

size_t	len_single_quote(char *str, size_t *i)
{
	size_t	len;
 
	++*i;
	while (str[*i] && str[*i] != '\'')
	{
		++*i;
		++len;
	}
	if (str[*i])
		++*i;
	return (len);
}

size_t	len_double_quote(char *str, size_t *i, char **env)
{
	size_t	len;
 
	while (str[++*i] && str[*i] != '\'')
		++len;
	if (str[*i])
		++*i;
	return (len);
}

size_t	len_arg(char *str, size_t *i, char **env)
{
	size_t	len;

	len = 0;
	while (str[*i] && !is_cmd_sep(str[*i]))
	{
		if (str[*i] == '\'')
			len += is_single_quote(str, i);
		else if (str[*i] == '"')
			len += is_double_quote(str, i, env);
		else
		
	}
	return (len);
}

size_t	count_args(char *str)
{
	
} 