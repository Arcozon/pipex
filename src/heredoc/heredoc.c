/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:27:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 16:38:13 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	rm_quotes_limiter(char *limiter)
{
	int		need_exp;
	char	quote;
	int		i;
	int		d_cpy;

	need_exp = 1;
	i = 0;
	d_cpy = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
		{
			need_exp = (++d_cpy, 0);
			quote = limiter[i];
			while (limiter[++i] && limiter[i] != quote)
				limiter[i - d_cpy] = limiter[i];
			if (limiter[i])
				break ;
			++d_cpy;
		}
		else
			limiter[i - d_cpy] = limiter[i];
		++i;
	}
	return (limiter[i - d_cpy] = 0, need_exp);
}

int	heredoc(char *limiter, char *p_name, char **env)
{
	int	fd_out;
	int	need_exp;
	int	mlv;

	need_exp = rm_quotes_limiter(limiter);
	mlv = 0;
	fd_out = heredoc_no_exp(limiter, p_name, &mlv);
	printf("--%d--\n", mlv);
	if (fd_out >= 0 && mlv && need_exp)
		fd_out = heredoc_exp(fd_out, env, mlv);
	return (fd_out);
}
// #include <stdio.h>

// int main(int ac, char **av, char **env)
// {
// 	char	lim[] = "'abc'\"123\"%";
// 	int	fd = heredoc(lim, ft_strrchr(av[0], '/') + 1, env);
// 	(void)ac;
// 	if (fd >= 0)
// 	{
// 		char	txt[512];
// 		int		br;
// 		do
// 		{
// 			br = read(fd, txt, 512);
// 			if (br < 0)
// 				return (write(2, "Merde\n", 6), 1);
// 			write(1, txt, br);
// 		}	while (br);
		
// 	}
// }
