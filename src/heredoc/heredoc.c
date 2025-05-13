/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:57:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/13 18:14:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_stdin(int fd, char *limiter)
{
	size_t	i
}

int	heredoc(char *limiter)
{
	int	doc_p[2];

	if (pipe(pipe) < 0)
		return (-1);
	read_stdin(doc_p[1], limiter);
	close(doc_p[1]);
	return (doc_p[0]);
}
