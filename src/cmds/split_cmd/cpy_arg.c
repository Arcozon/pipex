/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:38:02 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/13 14:53:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cpy_dollar(char *arg, size_t *i, char **pstr, char **env)
{
	size_t	len_vname;
	char	*vcontent;

	len_vname = len_var_name(++*pstr);
	if (!len_vname)
	{
		arg[*i] = '$';
		++*i;
	}
	else if (env)
	{
		while (*env)
		{
			if (!ft_strncmp_weq(*pstr, *env, len_vname))
			{
				vcontent = *env + len_vname + 1;
				while (*vcontent)
					arg[(*i)++] = *(vcontent++);
				break ;
			}
			++env;
		}
	}
	*pstr += len_vname;
}

void	cpy_single_quote(char *arg, size_t *i, char **pstr)
{
	++*pstr;
	while (**pstr && **pstr != '\'')
	{
		arg[*i] = **pstr;
		++*i;
		++*pstr;
	}
	if (**pstr)
		++*pstr;
}

void	cpy_double_quote(char *arg, size_t *i, char **pstr, char **env)
{
	++*pstr;
	while (**pstr && **pstr != '"')
	{
		if (**pstr == '$')
			cpy_dollar(arg, i, pstr, env);
		else
		{
			arg[*i] = **pstr;
			++*i;
			++*pstr;
		}
	}
	if (**pstr)
		++*pstr;
}

void	cpy_one_arg(char *arg, char **pstr, char **env)
{
	size_t	i;

	i = 0;
	while (**pstr && !is_cmd_sep(**pstr))
	{
		if (**pstr == '\'')
			cpy_single_quote(arg, &i, pstr);
		else if (**pstr == '"')
			cpy_double_quote(arg, &i, pstr, env);
		else if (**pstr == '$')
			cpy_dollar(arg, &i, pstr, env);
		else
		{
			arg[i] = **pstr;
			++*pstr;
			++i;
		}
	}
	arg[i] = 0;
}
