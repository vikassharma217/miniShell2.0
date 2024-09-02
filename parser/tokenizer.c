/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:29:55 by vsharma           #+#    #+#             */
/*   Updated: 2024/09/02 17:38:19 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (char_in_str(OPERATORS, *str))
			i++;
		if (char_in_str(QUOTES, *str) && *str == *(str + 1))
			str++;
		else if (char_in_str(QUOTES, *str))
			quotes = !quotes;
		if (*str != ' ' && !char_in_str(OPERATORS, *str) && !flag && !quotes)
		{
			flag = true;
			i++;
		}
		else if (*str == ' ' || char_in_str(OPERATORS, *str))
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
	if (char_in_str(OPERATORS, str[len]))
	{
		if (str[len] == str[len + 1])
			return (2);
		return (1);
	}
	while (str[len] && !ft_isspace(str[len]) && !char_in_str(OPERATORS,
			str[len]))
	{
		if (char_in_str(QUOTES, str[len]))
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
