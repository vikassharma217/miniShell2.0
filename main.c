/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:00:09 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/08 18:50:45 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to initialize minishell
int	init_minishell(char **env, t_data *data, t_cmd **cmd_list)
{
	if (isatty(STDIN_FILENO))
		data->mode = INTERACTIVE;
	else
		data->mode = NON_INTERACTIVE;
	data->env = env;
	data->env_lst = init_env_lst(env);
	data->head = NULL;
	data->exit_code = 0;
	data->is_pipe = 0;
	*cmd_list = NULL; //
	if (data->mode == INTERACTIVE)
		init_signal_interactive();
	else if (data->mode == NON_INTERACTIVE)
		init_signal_non_interactive();
	return (0);
}

// function to clean input from user
char	*get_cleaned_input(t_data *data)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		ft_clear_all(data);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(data->exit_code);
	}
	if (g_signal != 0)
		data->exit_code = 128 + SIGINT;
	return (strip_whitespace(input));
}

// main loop of minishell
void	minishell_loop(t_data *data, t_cmd **cmd_list)
{
	char	*input;
	char	*expanded_input;

	while (1)
	{
		input = get_cleaned_input(data);
		if (!input || *input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (!input_validation(input, data))
		{
			free(input);
			continue ;
		}
		expanded_input = init_expander(input, data);
		free(input);
		input = expanded_input;
		*cmd_list = init_parser(input);
		data->head = *cmd_list;
		start_execution(*cmd_list, data);
		free_parsed_tokens(cmd_list, data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_list;

	if (argc != 1 || argv[1])
		return (write(2, "Error: too many arguments\n", 26));
	if (!getenv("_"))
		return (write(2, "Error: Minishell: invalid environment\n", 39));
	init_minishell(env, &data, &cmd_list);
	minishell_loop(&data, &cmd_list);
	return (EXIT_SUCCESS);
}
