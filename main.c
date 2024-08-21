/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:00:09 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/21 12:04:14 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(char **env, t_data *data, t_cmd **cmd_list)
{
	//printf("Init minishell\n");
	if (isatty(STDIN_FILENO))
		data->mode = INTERACTIVE;
	else
		data->mode = NON_INTERACTIVE;
	data->env = env;
	if (env)
	{
		//printf("env is not null\n");
        data->env_lst = init_env_lst(env);
        if (!data->env_lst)
        {
            fprintf(stderr, "Failed to initialize environment list\n");
            return (1);
        }
    }
	else
	{
		data->env_lst = NULL;
	}
	data->head = NULL;
	data->exit_code = 0;
	*cmd_list = NULL;
	//handel_signals(data);
	return (0);
}

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

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;
	t_cmd	*cmd_list;

	//printf("Start of minishell\n");
	if (argc != 1 || argv[1])
		return (write(2, "Error: too many arguments\n", 26));
    if (!getenv("_"))
    {
        fprintf(stderr, "Error: minishell is not running in a valid environment\n");
        return (1);
    }
	if (init_minishell(env, &data, &cmd_list) != 0)
    {
        fprintf(stderr, "Failed to initialize minishell\n");
        return (1);
    }
	while (1)
	{
		input = clean_input(&data);
		if (!input || *input == '\0')
		{
			printf("input is empty\n");
			free(input);
			continue ;
		}
		add_history(input);
		if (!input_validation(input, &data))
			continue ;
		input = init_expander(input, &data);
		cmd_list = init_parser(input);
		data.head = cmd_list;
		//init_execution(cmd_list, &data);
		free_parsed_tokens(&cmd_list, &data);
	}
	return (EXIT_SUCCESS);
}