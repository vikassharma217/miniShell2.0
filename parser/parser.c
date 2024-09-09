/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:32:59 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/09 11:13:34 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Count the number of arguments in the parsed input
static int	count_arguments(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

/*assign the correct operator to parsed linked list*/
static t_op	assign_op(char *str)
{
	t_op	operator;

	if (!str)
		operator = NONE;
	else if (str_equals(str, ">"))
		operator = RD_OUT;
	else if (str_equals(str, ">>"))
		operator = RD_APND;
	else if (str_equals(str, "<"))
		operator = RD_IN;
	else if (str_equals(str, "<<"))
		operator = RD_HD;
	else if (str_equals(str, "|"))
		operator = PIPE;
	else
		operator = NONE;
	free(str);
	return (operator);
}

// Create a new node for the linked list
static t_cmd	*create_cmd_node(char **parsed, int *i)
{
	t_cmd	*temp;
	int		j;

	temp = newnode_par(count_arguments(parsed));
	j = 0;
	while (parsed[*i] && !char_in_str(OPERATORS, parsed[*i][0]))
	{
		temp->argv[j++] = handel_quotes(parsed[(*i)++]);
	}
	temp->argv[j] = NULL;
	if (parsed[*i])
		temp->operator = assign_op(parsed[(*i)++]);
	return (temp);
}

static char	**process_input(char *str)
{
	char	**token;

	token = allocate_token(str);
	if (!token)
		return (NULL);
	allocate_tokens_memory(token, str);
	fill_tokens(token, str);
	return (token);
}

// Init parser by processing the input & creating a linked lst of cmds
t_cmd	*init_parser(char *input)
{
	char	**tokenized;
	t_cmd	*temp;
	t_cmd	*head;
	int		i;

	tokenized = process_input(input);
	free(input);
	i = 0;
	temp = create_cmd_node(tokenized, &i);
	head = temp;
	while (tokenized[i])
	{
		temp->next = create_cmd_node(tokenized, &i);
		temp = temp->next;
	}
	temp->next = NULL;
	free(tokenized);
	return (head);
}
