/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:16:13 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/03 14:17:00 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//generating temp filename for heredoc
//allows because of index generating individuell filenames with _1 _2...

void	generate_filename(char *buffer, int index)
{
	int	length;

	ft_strncpy(buffer, "/tmp/.minishell_heredoc_", PATH_MAX);
	length = ft_strlen(buffer);
	buffer[length++] = '0' + index;
	buffer[length] = '\0';
}
