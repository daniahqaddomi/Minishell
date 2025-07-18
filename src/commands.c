/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:51 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/07/14 21:56:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_cd_command(char *path, int arg_count, t_data *data)
// {
// 	if (arg_count > 2)
// 	{
// 		printf("cd: too many arguments\n");
// 		data->last_status = 1;
// 		return ;
// 	}
// 	while (*path == ' ' || *path == '\t')
// 		path++;
// 	if (*path == '\0' || ft_strcmp(path, "~") == 0)
// 		path = getenv("HOME");
// 	if (chdir(path) != 0)
// 	{
// 		printf("cd: %s: No such file or directory\n", path);
// 		data->last_status = 1;
// 	}
// 	else
// 		data->last_status = 0;
// }

void	handle_echo_command(t_token *token)
{
	int	newline;

	newline = 1;
	token = token->next;
	while (token && ft_strcmp(token->value, "-n") == 0)
	{
		newline = 0;
		token = token->next;
	}
	while (token && (token->type == WORD
			|| token->type == COMMAND))
	{
		printf("%s", token->value);
		if (token->next && token->next->type == WORD)
			printf(" ");
		token = token->next;
	}
	if (newline)
		printf("\n");
}

// void	handle_type_command(const char *input, t_data *data)
// {
// 	char	*path_env;
// 	char	*dir;
// 	char	*full_path;

// 	if (is_shell_builtin(input))
// 	{
// 		printf("%s is builtin\n", input);
// 		return ;
// 	}
// 	path_env = ft_strdup(getenv("PATH"));
// 	if (path_env)
// 	{
// 		dir = ft_strtok(path_env, ":");
// 		while (dir != NULL)
// 		{
// 			full_path = path_join(dir, input);
// 			if (access(full_path, X_OK) == 0)
// 			{
// 				printf("%s is %s\n", input, full_path);
// 				free (path_env);
// 				return ;
// 			}
// 			dir = ft_strtok(NULL, ":");
// 		}
// 		free(path_env);
// 	}
// 	printf("%s: not found\n", input);
// 	data->last_status = 1;
// }
