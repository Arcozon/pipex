/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/09 16:26:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "flag_error.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define PATH_EQ "PATH="
# define PATH_EQ_LEN 5
# define HEREDOC "here_doc"
# define HEREDOC_LEN 8

# ifndef PPX_BONUS
#  define PPX_BONUS 0
# endif

typedef struct s_cmd
{
	char	*av_i;
	char	**av;
	char	*path;
	
	int		ifd;
	int		ofd;

	int		pid;
}	t_cmd;

typedef struct	s_pipex
{
	char	*av_0;

	char	*infile;
	char	heredoc:1;
	char	*outfile;
	char	*path;

	t_cmd	*cmds;
	size_t	nb_cmds;

	int		pipe[2];

	unsigned char	errors;
}	t_px;

#endif
