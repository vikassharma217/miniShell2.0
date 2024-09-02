/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:52:38 by rscherl           #+#    #+#             */
/*   Updated: 2024/09/02 17:03:37 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_and_print(const char *str)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		if (*str != '\\')
			write(1, str, 1);
		str++;
	}
}

static bool	check_n_flag(const char *argv)
{
	int	j;

	j = 1;
	if (argv[0] != '-')
		return (false);
	while (argv[j] == 'n')
		j++;
	return (argv[j] == '\0');
}

int	echo(t_cmd *cmd)
{
	bool	flag_for_n;
	int		i;

	flag_for_n = false;
	i = 0;
	while (++i < cmd->argc && check_n_flag(cmd->argv[i]))
		flag_for_n = true;
	while (i < cmd->argc)
	{
		check_and_print(cmd->argv[i]);
		if (i < cmd->argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!flag_for_n)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
