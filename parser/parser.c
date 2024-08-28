/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:32:59 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 11:53:27 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_argc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*assign the correct operator to parsed linked list*/
t_op	get_operator(char *str)
{
	t_op	operator;

	if (!str)
		operator= NONE;
	else if (ft_is_str_equal(str, ">"))
		operator= RD_OUT;
	else if (ft_is_str_equal(str, ">>"))
		operator= RD_APND;
	else if (ft_is_str_equal(str, "<"))
		operator= RD_IN;
	else if (ft_is_str_equal(str, "<<"))
		operator= RD_HD;
	else if (ft_is_str_equal(str, "|"))
		operator= PIPE;
	else
		operator= NONE;
	free(str);
	return (operator);
}

char	**process_input(char *str)
{
	char	**token;

	token = allocate_token(str);
	if (!token)
		return (NULL);
	allocate_tokens_memory(token, str);
	fill_tokens(token, str);
	return (token);
}

t_cmd	*create_cmd_node(char **parsed, int *i)
{
	t_cmd	*temp;
	int		j;

	temp = newnode_par(get_argc(parsed));
	j = 0;
	while (parsed[*i] && !ft_onstr(OPERATORS, parsed[*i][0]))
	{
		temp->argv[j++] = handel_quotes(parsed[(*i)++]);
	}
	temp->argv[j] = NULL;
	if (parsed[*i])
		temp->operator= get_operator(parsed[(*i)++]);
	return (temp);
}

t_cmd	*init_parser(char *input)
{
	char	**parsed;
	t_cmd	*temp;
	t_cmd	*head;
	int		i;

	parsed = process_input(input);
	free(input);
	i = 0;
	temp = create_cmd_node(parsed, &i);
	head = temp;
	while (parsed[i])
	{
		temp->next = create_cmd_node(parsed, &i);
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
