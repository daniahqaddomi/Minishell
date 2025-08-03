/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:49:43 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/03 19:43:41 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_token **token, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	if (!*token)
		*token = new;
	else
	{
		temp = *token;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

 //void	mark_commands(t_token *tokens)
// {
// 	t_token		*cur;
// 	int		expect_command;

// 	cur = tokens;
// 	expect_command = 1;
// 	while (cur)
// 	{
// 		if (cur->type == PIPE)
// 			expect_command = 1;
// 		else if (cur->type == WORD && expect_command)
// 		{
// 			cur->type = COMMAND;
// 			expect_command = 0;
// 		}
// 		cur = cur->next;
// 	}
// }

int		is_syntax_error(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
		return (1);
	while (cur)
	{
		if (cur->type == PIPE
			&& (!cur->next || cur->next->type == PIPE))
			return (1);
		if ((cur->type == REDIR_IN || cur->type == REDIR_OUT
				|| cur->type == APPEND || cur->type == HEREDOC)
			&& (!cur->next || cur->next->type != WORD))
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	tokenize(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (ft_strcmp(cur->value, "|") == 0)
			cur->type = PIPE;
		else if (ft_strcmp(cur->value, "<") == 0)
			cur->type = REDIR_IN;
		else if (ft_strcmp(cur->value, ">") == 0)
			cur->type = REDIR_OUT;
		else if (ft_strcmp(cur->value, ">>") == 0)
			cur->type = APPEND;
		else if (ft_strcmp(cur->value, "<<") == 0)
			cur->type = HEREDOC;
		else
			cur->type = WORD;
		cur = cur->next;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}
