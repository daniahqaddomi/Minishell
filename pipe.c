/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:53:51 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/07/31 11:27:44 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_command *command)
{
	command->argv = NULL;
	command->builtin_fun = 0;
	command->next_cmd = NULL;
	command->pid = 0;
	command->redirections = NULL;
}
// prepare empty room before put anything in it
t_command	*new_node(void)
{
	t_command	*new_command;

	new_command = (t_command *)malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("Malloc Failed");
		return (NULL);
	}
	return (new_command);
}
// adds the arg to the correct command list (add an argumant to a command argv array)
// dynamically reallocates the argv array
void	*add_argument(t_command *command, char *value)
{
	int	i;

	int current_count;
		// to track how many arg i add to command->argv (so i can know the current size to allocate enough space for the new array)
	char **new_argv;   // hold the new argv
	current_count = 0;
	i = 0;
	if (!command || !value)
		return (1);
	if (command->argv)
	{
		while (command->argv[current_count])
			current_count++;
	}
	new_argv = (char **)malloc(sizeof(char *) * (current_count + 2));
		// one for null and one for the new arg
	if (!new_argv)
	{
		perror("Error");
		return (1);
	}
	while (current_count > i)
	{
		new_argv[i] = command->argv[i];
		i++;
	}
	// free (new_argv);
	// return ;
	new_argv[current_count] = ft_strdup(value);
	if (!new_argv[current_count])
	{
		perror("strdup faild");
		free(new_argv);
		return (1);
	}
	new_argv[current_count + 1] = NULL; // for the new array
	free(command->argv);                // free the old argv
	command->argv = new_argv;
	if (current_count == 0 && command->argv[0]) // check i its a builtin command
		command->builtin_fun = ft_builtin(command->argv[0]);
	return (0);
}
