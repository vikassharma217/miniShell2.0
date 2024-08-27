/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:55:19 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/27 15:52:54 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

bool	ft_onstr(const char *str, int ch)
{
	size_t	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (true);
		i++;
	}
	return (false);
}

bool	ft_is_str_equal(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}

bool	export_state(char *name, t_elst **head)
{
	t_elst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (ft_is_str_equal(name, temp->name))
			return (temp->exported);
		temp = temp->next;
	}
	return (false);
}

int	store_usr_var(char *cmd, t_elst **head, bool export)
{
	char	**line;

	line = split_env_var(cmd);
	if (export_state(line[0], head) && !export)
		export = true;
	unset_variable(line[0], head);
	lstadd_back_env(head, newnode_env(line[0], line[1], export));
	free(line);
	return (EXIT_SUCCESS);
}

char	*trim_whitespace(char *str)
{
	const char	*start;
	const char	*end;
	size_t		len;
	char		*trimmed_str;

	start = str;
	end = str + ft_strlen(str) - 1;
	while (ft_isspace((unsigned char)*start))
		start++;
	while (end > start && ft_isspace((unsigned char)*end))
		end--;
	len = (end - start) + 1;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(trimmed_str, start, len);
	trimmed_str[len] = '\0';
	free(str);
	return (trimmed_str);
}