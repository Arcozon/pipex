/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/12 18:58:00 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "flag_error.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define PATH_EQ "PATH"
# define PATH_EQ_LEN 4
# define HEREDOC "here_doc"
# define HEREDOC_LEN 8

# ifndef PPX_BONUS
#  define PPX_BONUS 0
# endif

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	*pre_split;
	char	**args;
	char	*path;
	
	int		ifd;
	int		ofd;

	int		pid;

	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_pipex
{
	char	*av_0;

	char	*infile;
	char	heredoc:1;
	char	*outfile;
	char	*path;

	t_cmd	*cmds;

	int		pipe[2];

	unsigned char	errors;
}	t_px;

int		is_cmd_sep(char c);
int		is_var_name(char c);
size_t	len_var_name(char *str);
size_t	len_dollar(char	*str, size_t *i, char **env);
size_t	len_one_arg(char *str, size_t *i, char **env);
size_t	count_args(char *str, char **env);
void	cpy_one_arg(char *arg, char **pstr, char **env);

int		ft_strncmp_weq(char *name, char *var, size_t n);
size_t	ft_strlen(char *str);

void	free_split(char **split);

#endif
