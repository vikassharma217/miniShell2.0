/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:32:59 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/21 12:11:59 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	get_argc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*count number of token in input string*/
int	token_num(char *str)
{
	int		i;
	bool	flag;
	bool	quotes;

	i = 0;
	flag = false;
	quotes = false;
	while (*str)
	{
		if (ft_onstr(OPERATORS, *str))
			i++;
		if (ft_onstr(QUOTES, *str) && *str == *(str + 1))
			str++;
		else if (ft_onstr(QUOTES, *str))
			quotes = !quotes;
		if (*str != ' ' && !ft_onstr(OPERATORS, *str) && !flag && !quotes)
		{
			flag = true;
			i++;
		}
		else if (*str == ' ' || ft_onstr(OPERATORS, *str))
			flag = false;
		str++;
	}
	return (i);
}


int	token_len(char *str)
{
	int		len;
	char	quotes;

	len = 0;
	if (ft_onstr(OPERATORS, str[len]))
	{
		if (str[len] == str[len + 1])
			return (2);
		return (1);
	}
	while (str[len] && !ft_isspace(str[len]) && !ft_onstr(OPERATORS, str[len]))
	{
		if (ft_onstr(QUOTES, str[len]))
		{
			quotes = str[len++];
			while (str[len] && str[len] != quotes)
				len++;
		}
		len++;
	}
	return (len);
}

/*allocate memeory for the array of token by counting num of tokens*/
char	**allocate_token(char *str)
{
	char	**token;

	token = malloc(sizeof(char *) * (token_num(str) + 1));
	if (!token)
		return (NULL);
	return (token);
}

/*allocate memory for each token in token array*/
void	allocate_tokens_memory(char **token, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (str[i])
	{
		len = token_len(&str[i]);
		if (!len)
		{
			i++;
			continue ;
		}
		token[j] = malloc(sizeof(char) * (len + 1));
		if (!token[j])
		{
			while (j > 0)
				free(token[--j]);
			free(token);
			return ;
		}
		j++;
		i += len;
	}
}

/*fill token from the input string into token array*/
void	fill_tokens(char **token, char *str)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	while (str[i])
	{
		len = token_len(&str[i]);
		if (!len)
		{
			i++;
			continue ;
		}
		k = 0;
		while (str[i] && k < len)
			token[j][k++] = str[i++];
		token[j++][k] = '\0';
	}
	token[j] = NULL;
}

/*assign the correct operator to parsed linked list*/
t_op	get_operator(char *str)
{
	t_op	operator;

	if (!str)
		operator = NONE;
	else if (ft_is_str_equal(str, ">"))
		operator = RD_OUT;
	else if (ft_is_str_equal(str, ">>"))
		operator = RD_APND;
	else if (ft_is_str_equal(str, "<"))
		operator = RD_IN;
	else if (ft_is_str_equal(str, "<<"))
		operator = RD_HD;
	else if (ft_is_str_equal(str, "|"))
		operator = PIPE;
	else
		operator = NONE;
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
		temp->operator = get_operator(parsed[(*i)++]);
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