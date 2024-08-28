/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:18:20 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 12:28:07 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_oldpwd(t_elst **head)
{
	char	*temp;

	unset_variable("OLDPWD", head);
	temp = ft_strjoin("OLDPWD=", getenv("HOME"));
	store_usr_var(temp, head, true);
	free(temp);
}

void	free_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// Splits an environment variable string into a name and value pair.
char	**split_env_var(char *env)
{
	char	**output;
	int		i;

	output = malloc(sizeof(char *) * 3);
	if (!output)
		return (NULL);
	i = ft_strchr(env, '=') - env;
	output[0] = ft_substr(env, 0, i);
	if (!output[0])
	{
		free(output);
		return (NULL);
	}
	output[1] = ft_substr(env, i + 1, ft_strlen(&env[i]));
	if (!output[1])
	{
		free(output[0]);
		free(output);
		return (NULL);
	}
	output[2] = NULL;
	return (output);
}

// Initializes a linked list for the environment variables.
t_elst	*init_env_lst(char **env)
{
	t_elst	*head;
	t_elst	*temp;
	char	**line;
	size_t	i;

	line = split_env_var(env[0]);
	head = newnode_env(line[0], line[1], true);
	free(line);
	i = 1;
	temp = head;
	while (env[i])
	{
		line = split_env_var(env[i]);
		temp->next = newnode_env(line[0], line[1], true);
		free(line);
		temp = temp->next;
		i++;
	}
	init_oldpwd(&head);
	return (head);
}
