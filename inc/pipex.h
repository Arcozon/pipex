/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:33:28 by geudes            #+#    #+#             */
/*   Updated: 2023/01/21 02:57:44 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*--------------------Env----------------------*/
char			**get_path(char **env);
char			*get_exec(char **env, char *cmd);

/*-------------------Utils---------------------*/
unsigned int	ft_strlen(const char *caca);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			free_split(char **split);

#endif
