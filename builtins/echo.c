/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:49:36 by caslan            #+#    #+#             */
/*   Updated: 2024/05/08 13:59:22 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	ft_print(const char *str)
{
	while (*str)
	{
		if (*str != '\\')
			write(1, str, 1);
		str++;
	}
}

int echo(t_cmd *cmd)
{
    bool flag_for_n;
    int i;

	flag_for_n = false;
	i = 0;

    while (++i < cmd->argc && ft_is_str_equal(cmd->argv[i], "-n"))
        flag_for_n = true;
    while (i < cmd->argc)
    {
        ft_print(cmd->argv[i]); //printf("%s, cmd->argv[i]")?
        if (i < cmd->argc - 1)
            write(1, " ", 1); //printf(" ")?
        i++;
    }
    if (!flag_for_n)
        write(1, "\n", 1); //printf("\n")?

    return (EXIT_SUCCESS);
}

/*static void	ft_print(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

bool	ft_str_start(const char *str, const char *pre)
{
	while (*pre)
	{
		if (*pre++ != *str++)
			return (false);
	}
	return (true);
}

int	ft_echo(t_cmd *cmd, t_data *data)
{
	bool	flag_for_n;
	int		i;

	(void)data;
	i = 1;
	flag_for_n = false;
	while (i < cmd->argc && ft_str_start(cmd->argv[i], "-n"))
	{
		flag_for_n = true;
		i++;
	}
	while (i < cmd->argc)
	{
		ft_print(cmd->argv[i]);
		if (i < cmd->argc - 1)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (!flag_for_n)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}*/
