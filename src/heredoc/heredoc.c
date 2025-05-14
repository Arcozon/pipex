/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:57:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/14 16:02:10 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"

#include <unistd.h>

// neg error, 0 success, pos not found
int	read_start_line(int fd, char *limiter, char *c, int *br)
{
	size_t	i_l;

	i_l = 0;
	while (1)
	{
		*br = read(STDIN_FILENO, c, 1);
		if (!*br)
			continue ;
		if (*br < 0)
			return (-1);
		if (!limiter[i_l] && *c == '\n')
			return (0);
		if (*c != limiter[i_l])
			break ;
		++i_l;
	}
	write(fd, limiter, i_l);
	write(fd, c, 1);
	return (1);
}

int	read_stdin(int fd, char *limiter)
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
			if (!read_start_line(fd, limiter, &c, &br))
				break ;
			continue ;
		}
		br = read(STDIN_FILENO, &c, 1);
		if (br == 1)
			write(fd, &c, 1);
	}
	return (0);
}

int	heredoc(char *limiter)
{
	int	here_p[2];

	if (pipe(here_p) < 0 || read_stdin(here_p[1], limiter))
		return (-1);
	close(here_p[1]);
	return (here_p[0]);
}

int main()
{
	int	fd = heredoc("123");
	
	if (fd >= 0)
	{
		char	txt[512];
		int		br;
		do
		{
			br = read(fd, txt, 512);
			if (br < 0)
				return (write(2, "Merde\n", 6), 1);
			write(1, txt, br);
		}	while (br);
	}
}
