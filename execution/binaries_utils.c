/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscherl <rscherl@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:54:34 by rscherl           #+#    #+#             */
/*   Updated: 2024/08/24 17:54:35 by rscherl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msg_error(char *cmd, t_data *data)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_clear_all(data);
}

bool	is_str(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i += 1;
	}
	return (false);
}

bool	is_path(t_cmd *cmd)
{
	if (is_str(cmd->argv[0], '/'))
		return (true);
	return (false);
}

char	*concat_and_free(char *str1, char *str2)
{
	size_t	len_str1;
	size_t	len_str2;
	char	*result;
	size_t	i;
	size_t	j;

	if (!str1 || !str2)
		return (NULL);
	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	result = malloc((len_str1 + len_str2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_str1)
		result[i++] = str1[j++];
	j = 0;
	while (j < len_str2)
		result[i++] = str2[j++];
	result[i] = '\0';
	free(str1);
	return (result);
}
