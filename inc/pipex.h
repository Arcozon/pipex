/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:27:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/20 11:37:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "flag_error.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define PATH_EQ "PATH="
# define PATH_EQ_LEN 5
# define HEREDOC "here_doc"
# define HEREDOC_LEN 8

# ifndef PPX_BONUS
#  define PPX_BONUS 1
# endif

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char			*pre_split;
	char			**args;
	char			*path;

	int				infd;
	int				outfd;

	int				pid;

	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	char			*p_name;

	char			*infile;
	unsigned int	heredoc:1;
	int				ifd;
	char			*outfile;
	int				ofd;

	char			*path;
	char			**env;

	t_cmd			*cmds;

	int				last_in;

	unsigned char	errors;
	int				r_value;
}	t_px;

size_t	len_var_name(char *str);
size_t	len_dollar(char	*str, size_t *i, char **env);
size_t	len_one_arg(char *str, size_t *i, char **env);
size_t	count_args(char *str, char **env);
void	cpy_one_arg(char *arg, char **pstr, char **env);

char	**split_cmd(char *str, char **env);

int		heredoc_exp(int fdin, char **env, int mlv);
int		heredoc_no_exp(char *limiter, char *p_name, int *mlv);
int		heredoc(char *limiter, char *p_name, char **env);

void	exec_cmds(t_px* px);
int		files_cmd(t_cmd *cmd, t_px *px);
void	make_a_child(t_cmd *cmd, t_px *px);

void	close_fd(int *fd);

char	**split_cmd(char *str, char **env);
char	*find_exe(char *exe_name, char *path, char *p_name);
void	find_exe_cmds(t_cmd *cmds, char *path, char *p_name);
t_cmd	*init_cmds(char	**av, size_t nb_cmds, t_px *px);

int		init_pipex(t_px *ppx,int ac,char *av[],char *env[]);
void	wait_childs(t_px *px);

int		is_cmd_sep(char c);
int		is_var_name(char c);
int		ft_isdigit(char c);
int		ft_strncmp_weq(char *name, char *env_var, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *str);
size_t	ft_strlen(char *str);
char	*ft_strrchr(char *str, char c);
char	*ft_substrjoin_with_slash(char *path, char *exe, size_t len);
int		slashchr(char *str);

void	putstrerr(char *err);
void	err_expected_delim(char *limiter, char *p_name, int to_print);
void	err_file(char *f_name, char *p_name);
void	px_error(char *p_name, char *error);
void	print_errors(unsigned char errors, char *p_name);
void	err_cmd_not_found(char *p_name, char *cmd);

void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_lst_cmd(t_cmd *lst);
void	free_px(t_px *px);

#endif
