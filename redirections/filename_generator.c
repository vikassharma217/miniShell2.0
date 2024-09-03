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

void	generate_filename(char *buffer, int index)
{
	int	length;

	ft_strncpy(buffer, "/home/rscherl/Rene/42_Github_Rene_privat/Projects/minishell/temp/.minishell_heredoc_", PATH_MAX);
	/*ft_strncpy(buffer, "/tmp/.minishell_heredoc_", PATH_MAX);*/
	length = ft_strlen(buffer);
	buffer[length++] = '0' + index;
	buffer[length] = '\0';
}