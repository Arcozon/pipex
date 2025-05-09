/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:18:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/09 15:38:47 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipex(t_px *ppx,int ac,char *av[],char *env[])
{
	if (ac < 5)
		return (1);
	ppx->av_0 = av[0];
	ppx->heredoc = 0;
	if (PPX_BONUS)
		ppx->heredoc = ft_strncmp(HEREDOC, av[1]) == 0;
	
	return (0);
}