/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhaddadi <jhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:46:42 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/07/14 13:46:42 by jhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_token_with_multiple(t_token **head, t_token *cur, char **parts)
{
	t_token	*new_list = NULL;
	t_token	*tail = NULL;
	t_token	*temp = *head;
	t_token	*part_tokens = NULL;
	t_token	*part_tail = NULL;
	int		i;

	// Step 1: build list from parts[]
	i = 0;
	while (parts[i])
	{
		create_token(&part_tokens, parts[i], UNKNOWN);
		i++;
	}

	// Step 2: find last token in parts[]
	part_tail = part_tokens;
	while (part_tail && part_tail->next)
		part_tail = part_tail->next;

	// Step 3: rebuild new list
	while (temp)
	{
		if (temp == cur)
		{
			// insert full parts list instead of cur
			if (!new_list)
				new_list = part_tokens;
			else
				tail->next = part_tokens;

			tail = part_tail;
		}
		else
		{
			create_token(&new_list, temp->value, temp->type);
			if (!tail)
				tail = new_list;
			else
			{
				tail = tail->next;
			}
		}
		temp = temp->next;
	}

	// Step 4: free old token list
	free_tokens(*head);
	*head = new_list;

	// Step 5: cleanup parts array
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}
