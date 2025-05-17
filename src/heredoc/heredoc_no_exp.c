/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_no_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:57:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 16:38:07 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define EXP_LIM 2

// neg error, pos success, 0 not found
int	read_start_line(int fd, char *limiter, char *c, int *br)
{
	size_t	i_l;

	i_l = 0;
	while (1)
	{
		*br = read(STDIN_FILENO, c, 1);
		if (*br < 0)
			return (-1);
		if (!*br && i_l == 0)
			return (EXP_LIM);
		else if (!*br)
			continue ;
		if (!limiter[i_l] && *c == '\n')
			return (0);
		if (*c != limiter[i_l])
			break ;
		++i_l;
	}
	write(fd, limiter, i_l);
	return (1);
}

// act_len is the len of the var name we are in
void	heredoc_handle_dollar(char c, int *mlv)
{
	static int	act_len = -1;
	int			out;

	out = 0;
	if (c == '$' && act_len == -1)
		act_len = 0;
	else if (act_len != -1)
	{
		if (act_len == 0 && (c >= '0' && c <= '9'))
			out = (++act_len, 1);
		else if (is_var_name(c))
			++act_len;
		else
			out = 1;
	}
	if (out)
	{
		if (*mlv < act_len)
			*mlv = act_len;
		act_len = -1;
	}
}

int	read_stdin(int fd, char *limiter, char *p_name, int *mlv)
{
	char	c;
	int		br;

	c = '\n';
	br = 1;
	while (1)
	{
		if (br < 0)
			return (-1);
		if (c == '\n')
		{
			write(1, "> ", 2);
			br = read_start_line(fd, limiter, &c, &br);
			err_expected_delim(limiter, p_name, br == EXP_LIM);
			if (br == 0 || br == EXP_LIM)
				break ;
			if (br < 0)
				return (-1);
		}
		else
			br = read(STDIN_FILENO, &c, 1);
		if (br == 1)
			(write(fd, &c, 1), heredoc_handle_dollar(c, mlv));
	}
	return (0);
}

int	heredoc_no_exp(char *limiter, char *p_name, int *mlv)
{
	int	here_p[2];

	if (pipe(here_p) < 0)
		return (-1);
	if (read_stdin(here_p[1], limiter, p_name, mlv))
		here_p[0] = (close(here_p[0]), -1);
	close(here_p[1]);
	return (here_p[0]);
}
