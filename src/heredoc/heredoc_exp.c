/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:28:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/20 10:41:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_var_content(char *var_name, int lvar, char **env, int fdout)
{
	if (!lvar)
	{
		write(fdout, "$", 1);
		return ;
	}
	while (*env)
	{
		if (ft_strncmp_weq(var_name, *env, lvar) == 0)
			break ;
		++env;
	}
	if (*env)
		write(fdout, *env + lvar + 1, ft_strlen(*env + lvar + 1));
}

// Shitty implementation by me makes it so i need to have it recursive
// (Once i read the char that not in the var_name i might need to call 
// read var name again if its a $, otherwise its lost before the check for $
// in the read_fd_exp fct)  -- shoudl implement like the len calc in no_exp.c
int	read_var_name(int fdin, int fdout, char *var_name, char **env)
{
	int		lvar;
	int		br;
	char	c;

	lvar = 0;
	while (1)
	{
		br = read(fdin, &c, 1);
		if (br < 0)
			return (-1);
		if (br == 0 || !is_var_name(c))
			break ;
		var_name[lvar] = c;
		++lvar;
		if (lvar == 1 && ft_isdigit(c))
			break ;
	}
	write_var_content(var_name, lvar, env, fdout);
	if (br && !ft_isdigit(c) && c != '$')
		write(fdout, &c, 1);
	else if (br && c == '$')
		return (read_var_name(fdin, fdout, var_name, env));
	return (br > 0);
}

int	read_fd_exp(int fdin, int fdout, char *var_name, char **env)
{
	char	c;
	int		br;

	br = 1;
	while (1)
	{
		br = read(fdin, &c, 1);
		if (br < 0)
			return (-1);
		if (!br)
			return (0);
		if (c == '$' && read_var_name(fdin, fdout, var_name, env) == -1)
			return (-1);
		else if (c != '$')
			write(fdout, &c, 1);
	}
	return (0);
}

int	heredoc_exp(int fdin, char **env, int mlv)
{
	char	*var_name;
	int		hpipe[2];

	var_name = malloc(sizeof(char) * mlv);
	if (!var_name)
		return (close(fdin), -1);
	if (pipe(hpipe) < 0)
		return (close(fdin), free(var_name), -1);
	if (read_fd_exp(fdin, hpipe[1], var_name, env) == -1)
		hpipe[0] = (close(hpipe[0]), -1);
	close(fdin);
	close(hpipe[1]);
	free(var_name);
	return (hpipe[0]);
}
