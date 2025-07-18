/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:43:37 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/07/11 12:38:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar(char *input, int *i, t_data *data)
{
	char	*name;
	char	*value;
	int		start;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_status));
	}
	else if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (ft_strdup(""));

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = getenv(name);
	free(name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*handle_double_quote(char *input, int *i, t_data *data)
{
	char	*res = ft_strdup("");
	char	*temp;
	int		start;

	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			temp = handle_dollar(input, i, data);
			res = join_and_free(res, temp);
		}
		else
		{
			start = (*i)++;
			temp = ft_substr(input, start, 1);
			res = join_and_free(res, temp);
		}
	}
	if (input[*i] == '"')
		(*i)++;
	return (res);
}

char	*handle_single_quote(char *input, int *i)
{
	int		start;
	char	*quoted;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	quoted = ft_substr(input, start, *i - start);
	if (input[*i] == '\'')
		(*i)++;
	return (quoted);
}

char	*join_and_free(char *a, char *b)
{
	char	*res;

	if (!a && !b)
		return (NULL);
	else if (!a)
		return (ft_strdup(b));
	else if (!b)
		return (ft_strdup(a));
	res = ft_strjoin(a, b);
	free(a);
	return (res);
}

char	*expand_token_value(char *input, t_data *data)
{
	char	*temp;
    char    *result;
    int     i;

    i = 0;
    result = ft_strdup("");
    while (input[i])
    {
	    if (input[i] == '\'')
		    temp = handle_single_quote(input, &i);
	    else if (input[i] == '"')
		    temp = handle_double_quote(input, &i, data);
	    else if (input[i] == '$')
		    temp = handle_dollar(input, &i, data);
            else
		    temp = ft_substr(input, i++, 1);
        result = join_and_free(result, temp);
    }
    return (result);
}

int     is_quoted (char *str)
{
	int     len;
    
    len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') ||
					(str[0] == '"' && str[len - 1] == '"')))
		return (1);
	return (0);
}

void	expand (t_token *tokens, t_data *data)
{
	t_token     *cur;
	char	*expanded;
    char    **parts;
    int     j;

	cur = tokens;
	while (cur)
	{
		expanded = expand_token_value(cur->value, data);
		if (expanded && ft_strchr(expanded, ' ') && !is_quoted(cur->value))
		{
			parts = ft_split(expanded, ' ');
            replace_token_with_multiple(&tokens, cur, parts);
            j = 0;
            while (parts[j])
	            free(parts[j++]);
            free(parts);
            free(expanded);
            return;
		}
		free(cur->value);
		cur->value = expanded;
		cur = cur->next;
	}
}
