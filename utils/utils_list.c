/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:47:03 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/27 13:03:29 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//creat new node for parsed token linked list
t_cmd	*newnode_par(int argc)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	if (!new_node->argv)
		return (NULL);
	new_node->operator= NONE;
	new_node->next = NULL;
	return (new_node);
}

char	*get_fromvlst(char *var_name, t_elst **head)
{
	t_elst	*temp;

	temp = *head;
	if (!var_name || !head)
		return (NULL);
	while (temp != NULL)
	{
		if (ft_is_str_equal(var_name, temp->name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*get_varvalue_fromvlst(char *var_name, t_data *data)
{
	char	*var_value;

	if (!var_name || !data)
		return (NULL);
	var_value = get_fromvlst(var_name, &data->env_lst);
	if (!var_value)
	{
		free(var_name);
		return (NULL);
	}
	free(var_name);
	return (var_value);
}

t_elst	*lstlast_env(t_elst *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

void	lstadd_back_env(t_elst **head, t_elst *new)
{
	t_elst	*temp;

	if (head)
	{
		if (!*head)
			*head = new;
		else
		{
			temp = lstlast_env(*(head));
			temp->next = new;
		}
	}
}

bool	is_digit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}

long long	ft_atol(const char *str)
{
	long long	res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i += 1;
	}
	return (res * signal);
}

static long long	ft_digits(long long n)
{
	long long	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_lltoa(long long n)
{
	long long	digits;
	int			signal;
	char		*result;

	digits = ft_digits(n);
	signal = 1;
	result = malloc((digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[digits--] = '\0';
	if (n < 0)
	{
		signal = -1;
		result[0] = '-';
	}
	else if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		result[digits--] = (n % 10 * signal) + '0';
		n /= 10;
	}
	return (result);
}

// Creates a new node for an environment variable linked list.

t_elst	*newnode_env(char *var_name, char *var_value, bool is_exported)
{
	t_elst	*new_node;

	new_node = malloc(sizeof(t_elst));
	if (!new_node)
		return (NULL);
	new_node->name = var_name;
	new_node->value = var_value;
	new_node->exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}
