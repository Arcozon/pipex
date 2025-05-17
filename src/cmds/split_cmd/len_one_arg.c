/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_one_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:10:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 19:13:19 by gaeudes          ###   ########.fr       */
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
	len = 0;
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

	++*i;
	len = 0;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			len += len_dollar(str, i, env);
		else
		{
			++*i;
			++len;
		}
	}
	if (str[*i])
		++*i;
	return (len);
}

size_t	len_one_arg(char *str, size_t *i, char **env)
{
	size_t	len;

	len = 0;
	while (str[*i] && !is_cmd_sep(str[*i]))
	{
		if (str[*i] == '\'')
			len += len_single_quote(str, i);
		else if (str[*i] == '"')
			len += len_double_quote(str, i, env);
		else if (str[*i] == '$')
			len += len_dollar(str, i, env);
		else
		{
			++len;
			++*i;
		}
	}
	return (len);
}

size_t	count_args(char *str, char **env)
{
	size_t	nb_args;
	size_t	i;

	i = 0;
	nb_args = 0;
	while (is_cmd_sep(str[i]))
		++i;
	while (str[i])
	{
		len_one_arg(str, &i, env);
		++nb_args;
		while (is_cmd_sep(str[i]))
			++i;
	}
	return (nb_args);
}
