/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:00:09 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/26 16:57:00 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Validate input and perform expansion
int	validate_and_expand_input(char **input, t_data *data)
{
	if (!*input || **input == '\0')
	{
		//printf("input is empty\n");
		return (0);
	}
	add_history(*input);
	if (!input_validation(*input, data))
		return (0);
	*input = init_expander(*input, data);
	if (!*input)
		return (0);
	return (1);
}

int	validate_input(char *input, t_data *data, t_cmd **cmd_list)
{
	// Validate and expand the input
	if (!validate_and_expand_input(&input, data))
	{
		free(input);
		return (1); // Continue the loop
	}
	// Parse and execute the command list
	*cmd_list = init_parser(input);
	if (!*cmd_list)
	{
		free(input);
		return (1); // Continue the loop
	}
	data->head = *cmd_list;
	start_execution(*cmd_list, data);
	free_parsed_tokens(cmd_list, data);
	//free(input);
	return (1); // Continue the loop
}

// Initialize the shell, environment, and data structures
int	init_minishell(char **env, t_data *data, t_cmd **cmd_list)
{
	if (isatty(STDIN_FILENO))
	{
		data->mode = INTERACTIVE;
		//printf("Interactive mode\n");
	}
	else
	{
		data->mode = NON_INTERACTIVE;
		//printf("Non-interactive mode\n");
	}
	data->env = env;
	if (env)
	{
		data->env_lst = init_env_lst(env);
		if (!data->env_lst)
		{
			ft_putstr_fd("Failed to initialize environment list\n", 2);
			return (1);
		}
	}
	else
		data->env_lst = NULL;
	data->head = NULL;
	data->exit_code = 0;
	*cmd_list = NULL;
	return (0);
}

// Handle input cleaning, freeing, and prompt exit (Ctrl+D)
char	*clean_input(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		ft_clear_all(data);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (g_signal != 0)
		data->exit_code = 130;
	return (trim_whitespace(input));
}

// Main entry point
int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_list;
	char	*input;

	if (argc != 1 || argv[1])
	{
		 ft_putstr_fd("Error: too many arguments\n", 2);
        return (EXIT_FAILURE);
	}
	if (!getenv("_")) 
	{
		ft_putstr_fd("Error: minishell is not running in a valid environment\n", 2);
        return (EXIT_FAILURE);
	}

	if (init_minishell(env, &data, &cmd_list) != 0)
		return (EXIT_FAILURE);
	while (1)
	{
		input = clean_input(&data);
		if (!validate_input(input, &data, &cmd_list))
			break ;
	}
	return (EXIT_SUCCESS);
}
