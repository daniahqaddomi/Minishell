/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:51:50 by jhaddadi          #+#    #+#             */
/*   Updated: 2025/08/04 13:37:49 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*get_input(t_data *data)
{
	char	*line;

	line = readline("$ ");
	if (line == NULL)
	{
		printf("exit\n");
		exit(data->last_status);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

void	shell_loop(t_data *data)
{
	t_token	*tokens;
	char	*line;

	while (1)
	{
		set_signals_interactive();
		line = get_input(data);
		tokens = split_line_to_words(line);
		// if (!tokens) //to test it
		// 	continue ;
		// t_token *tmp = tokens;
		// while (tmp)
		// {
		// 	printf("Token: '%s'\n", tmp->value);
		// 	tmp = tmp->next;
		// }
		if (!tokens)
			continue ;
		expand(tokens, data);
		tokenize(tokens);
		if (is_syntax_error(tokens))
		{
			data->last_status = 258;//edit status
			free_tokens(tokens);
			continue ;
		}
		// mark_commands(tokens);
		// TODO: parse and execute here
		execute_builtin_tokens(tokens, data);
		free_tokens(tokens);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = copy_env(envp);
	data.last_status = 0;
	setbuf(stdout, NULL);
	shell_loop(&data);
	rl_clear_history();
	return (data.last_status);
}
