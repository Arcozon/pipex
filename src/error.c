/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:07:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/05/17 16:21:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	putstrerr(char *err)
{
	write(2, err, ft_strlen(err));
}
void	err_expected_delim(char *limiter, char *p_name, int to_print)
{
	if (!to_print)
		return ;
	putstrerr("\n");
	putstrerr(p_name);
	putstrerr(" :warning: here-document delimited by end-of-file (wanted '");
	putstrerr(limiter);
	putstrerr("')\n");
}
