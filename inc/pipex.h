/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:33:28 by geudes            #+#    #+#             */
/*   Updated: 2023/01/22 01:28:04 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int			**pipes;
	pid_t		*pids;
	int			nb_cmd;
	int			input;
	int			output;
	int			infile;
	int			outfile;
	char		**path;
}				t_pipex;

/*--------------------Env----------------------*/
char			**get_path(char **env);
char			*get_exec(char **path, char *cmd);

/*--------------------Pipex--------------------*/
t_pipex			*init_pipex(int nb_cmd, char **av, char **env);

/*-------------------Utils---------------------*/
unsigned int	ft_strlen(const char *caca);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			free_split(char **split);

#endif
