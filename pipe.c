/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:53:51 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/07/30 16:40:13 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_command     *command)
{
    command->argv = NULL;
    command->builtin_fun = 0;
    command->next_cmd = NULL;
    command->pid = 0;
    command->redirections = NULL;
}
//prepare empty room before put anything in it
t_command   *new_node(void)
{
    t_command   *new_command;
    
    new_command = (t_command *) malloc (sizeof(t_command));
    if (!new_command)
    {
        perror("Malloc Failed");
        return (NULL);
    }
    return (new_command);
}
//adds the arg to the correct command list
void    *add_argument(t_command *command, char value)
{
    int     current_count; //so i can track how many arg i add to command->argv (so i can know the current size to allocate enough space for the new array)
    char    **new_argv; //hold the new argv
    int     i;
    
    current_count = 0;
    i = 0;
    if (!current_count || !new_argv)
        return (NULL);
    if (command->argv)
    {
        while (command->argv[current_count])
            current_count++;
    }
    new_argv = (char **)malloc(sizeof (char *) * (current_count * 2)); //one for null and one for the new arg
    if (!new_argv)
    {
        perror("Error");
        return (NULL);
    }
        while (current_count > i)
        {
            free (new_argv[i]);
            i++;
        }
        free (new_argv);
        return;
}


















 // Deep copy the new argument string
    new_argv_array[current_arg_count] = ft_strdup(arg_val);
    if (!new_argv_array[current_arg_count])
    {
        perror("minishell: strdup failed for command argument");
        // Clean up the partially allocated new_argv_array before returning
        for (int i = 0; i < current_arg_count; i++) free(new_argv_array[i]); // Free duplicated strings
        free(new_argv_array);
        return;
    }
    new_argv_array[current_arg_count + 1] = NULL; // Null-terminate the array

    free(cmd->argv); // Free the old argv array (not the strings it pointed to, as they are now in new_argv_array)
    cmd->argv = new_argv_array;

    // If this is the first argument, check if it's a builtin command
    if (current_arg_count == 0 && cmd->argv[0])
        cmd->is_builtin = is_builtin_command(cmd->argv[0]); // is_builtin_command should be in builtins.c