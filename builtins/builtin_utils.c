/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:02:02 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/10 13:49:42 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_cd_error(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	write(2, "No such file or directory: ", 28);
	write(2, target_dir, ft_strlen(target_dir));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

static void	swap_env_vars(t_elst *a, t_elst *b)
{
	char	*tmp_name;
	char	*tmp_value;
	bool	tmp_exported;

	tmp_name = a->name;
	a->name = b->name;
	b->name = tmp_name;
	tmp_value = a->value;
	a->value = b->value;
	b->value = tmp_value;
	tmp_exported = a->exported;
	a->exported = b->exported;
	b->exported = tmp_exported;
}

void	sort_env_list(t_elst **env_list)
{
	t_elst	*current;
	t_elst	*next;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strncmp(current->name, next->name, PATH_MAX) > 0)
				swap_env_vars(current, next);
			next = next->next;
		}
		current = current->next;
	}
}
