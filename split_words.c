/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:00:08 by daniah            #+#    #+#             */
/*   Updated: 2025/08/03 19:38:46 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char s)
{
	if (s == ' ' || s == '\t' || s == '\n')
		return (1);
	else
		return (0);
}

static int	isspecial_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

static int	handle_quotes(const char *line, int i, char quote, int *new_pos)
{
	i++; // see what after the quote
	while (line[i] && line[i] != quote)
		// loop until reach the end or find closing
		i++;
	if (!line[i])
		return (0); // unmatched quote
	*new_pos = i + 1;
	return (1);
}

int	count_tokens(const char *line) // count how many words inside quote
{
	int count;
	int i;
	int new_pos;

	count = 0;
	i = 0;
	while (*line)
	{
		while (ft_isspace(line[i])) // skip spaces
			i++;
		if (!line[i]) // if reached end after spaces
			break ;
		count++;                           // found word(token)
		if (!ft_isspace(line[i]) && !isspecial_char(line[i]) && line[i] != '\'' && line[i] != '"') // if start with a quote
		{
			if (!handle_quotes(line, i, line[i], &new_pos))
				return (-1); // unmatched
			i = new_pos;     // move i after the quote
		}
		else
			while (line[i] && !ft_isspace(line[i]) && line[i] != '"'
				&& line[i] != '/')
				i++;
	}
	return (count);
}

static int	token_length(const char *line, int *i)
{
	int	start;
	int	len;
	int new_pos;

	start = *i;
	len = 0;
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (!handle_quotes(line, *i, line[*i], &new_pos))
			return (-1);
		*i = new_pos;
		len = *i - start;		// the length is from the opining quote (start) to where the closing was found (*i)
	}
	else if (isspecial_char(line[*i]))
	{
		if (line[*i + 1] && ((line[*i] == '>' && line[*i + 1] == '>')
				|| (line[*i] == '<' && line[*i + 1] == '<'))) // for (<<)
		{
			len = 2; // cuz its 2 char
			*i += 2;
		}
		else // if its one char (<,>,|)
		{
			len = 1;
			(*i)++;
		}
	}
		else
		{
			while (line[*i] && !ft_isspace(line[*i])
				&& !isspecial_char(line[*i]))
				(*i)++;
			len = *i - start;
		}
		return (len);
	}

static char	*extract_token(const char *line, int *i, int len)
		// It allocates memory and extracts a substring of len characters from the input line,ending at position *i.
{
	char *token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, line + *i - len, len + 1);
	return (token);
}

t_token *split_line_to_words(char *line)
{
    int i = 0;
    int len;
    t_token *head = NULL;
    t_token *tail = NULL;
    char *token_str;

    if (!line || !*line)
        return NULL;

    while (line[i])
    {
        while (ft_isspace(line[i]))
            i++;
        if (!line[i])
            break;

        len = token_length(line, &i);
        if (len < 0)
        {
            free_tokens(head);
            return NULL;
        }

        token_str = extract_token(line, &i, len);
        if (!token_str)
        {
            free_tokens(head);
            return NULL;
        }

        t_token *new_node = malloc(sizeof(t_token));
        if (!new_node)
        {
            free(token_str);
            free_tokens(head);
            return NULL;
        }

        new_node->value = token_str;
        new_node->type = WORD;  //  UNKNOWN  
        new_node->next = NULL;

        if (!head)
            head = new_node;
        else
            tail->next = new_node;

        tail = new_node;
    }
    return head;
}

// char	**split_line_to_words(char *line)
// {
// 	int		i;
// 	int		count_token;
// 	int		index;
// 	char	**tokens;
// 	int		len;

// 	if (!line || !*line)
// 		return (0);
// 	count_token = count_tokens(line);
// 	if (count_token <= 0)
// 	{
// 		if (count_token == 0)
// 			return (ft_calloc(1, sizeof(char *)));
// 	else
// 		return (NULL);
// 	}
// 	tokens = malloc((count_token + 1) * sizeof(char *));
// 	if (!tokens)
// 		return (NULL);
// 	i = 0;
// 	index = 0;
// 	while (line[i] && index < count_token)
// 	{
// 		while (ft_isspace(line[i]))
// 			i++;
// 		if (!line[i])
// 			break ;
// 		len = token_length(line, &i);
// 		if (len < 0)
// 		{
// 			ft_free(tokens);
// 			return (NULL);
// 		}
// 		tokens[index] = extract_token(line, &i, len);
// 		if (!tokens[index])
// 		{
// 			ft_free(tokens);
// 			return (NULL);
// 		}
// 		index++;
// 	}
// 	tokens[index] = NULL;
// 	return (tokens);
// }
