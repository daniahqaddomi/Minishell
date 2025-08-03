/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:47:55 by marvin            #+#    #+#             */
/*   Updated: 2025/07/14 14:47:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this file is only for testing and the logic might change
char	**tokens_to_argv(t_token *start)
{
	t_token	*cur = start;
	char	**argv;
	int		count = 0;
	int		i = 0;

	while (cur && (cur->type == COMMAND || cur->type == WORD))
	{
		count++;
		cur = cur->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	cur = start;
	while (i < count)
	{
		argv[i++] = ft_strdup(cur->value);
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

// Free char **argv array
void	free_argv(char **argv)
{
	int	i = 0;

	while (argv && argv[i])
		free(argv[i++]);
	free(argv);
}

void	execute_builtin_tokens(t_token *tokens, t_data *data)
{
	t_token	*cur = tokens;
	char	**argv;

	while (cur)
	{
		if (cur->type == COMMAND)
		{
			argv = tokens_to_argv(cur);
			if (!argv)
				return ;
			if (ft_strcmp(argv[0], "echo") == 0)
				handle_echo_command(tokens);
			 else if (ft_strcmp(argv[0], "cd") == 0)
				handle_cd_command(argv, data);
			// else if (ft_strcmp(argv[0], "pwd") == 0)
			// 	handle_pwd_command();
			else if (ft_strcmp(argv[0], "export") == 0)
				handle_export_command(argv, data);
			else if (ft_strcmp(argv[0], "unset") == 0)
				handle_unset_command(argv, data);
			else if (ft_strcmp(argv[0], "env") == 0)
				handle_env_command(argv, data);
			else if (ft_strcmp(argv[0], "exit") == 0)
				handle_exit_command(argv, data);
			else
				printf("Command not found: %s\n", argv[0]);
			free_argv(argv);
			break ;
		}
		cur = cur->next;
	}
}
