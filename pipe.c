/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:53:51 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/07/31 15:11:28 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(t_parsing   *parsing)
{
    parsing->argv = NULL;
    parsing->builtin_fun = 0;
    parsing->next_cmd = NULL;
    parsing->pid = 0;
    parsing->redirections = NULL;
}
//prepare empty room before put anything in it
t_parsing   *new_node(void)
{
    t_parsing   *new_command;
    
    new_command = (t_parsing *) malloc (sizeof(t_parsing));
    if (!new_command)
    {
        perror("Malloc Failed");
        return (NULL);
    }
    ft_initialize(new_command);
    return (new_command);
}
//adds the arg to the correct command list (add an argumant to a command argv array)
//dynamically reallocates the argv array 
int    add_argument(t_parsing *parsing, char *value)
{
    int     current_count; //to track how many arg i add to command->argv (so i can know the current size to allocate enough space for the new array)
    char    **new_argv; //hold the new argv
    int     i;
    
    current_count = 0;
    i = 0;
    if (!parsing || !value)
        return (1);
    if (parsing->argv)
    {
        while (parsing->argv[current_count])
            current_count++;
    }
    new_argv = (char **)malloc(sizeof (char *) * (current_count + 2)); //one for null and one for the new arg
    if (!new_argv)
    {
        perror("Error");
        return (1);
    }
    while (current_count > i)
    {
        new_argv[i] = parsing->argv[i];
        i++;
    }
    new_argv[current_count] = ft_strdup(value);
    if (!new_argv[current_count])
    {
        perror("strdup faild");
        free (new_argv);
        return (1);
    }
    new_argv[current_count + 1] = NULL; //for the new array
    free(parsing->argv); // free the old argv 
    parsing->argv = new_argv;
    if (current_count == 0 && parsing->argv[0]) //check i its a builtin command
        parsing->builtin_fun = is_builtin(parsing->argv[0]);
    return (0);
}

void    add_redirection (t_parsing  *parsing, t_token_type  type, char  *filename)
{
    t_token     *new_redir;
    t_token     *current_redir;
    
    if (!parsing || !filename)
        return;
    new_redir = (t_token *)malloc(sizeof(t_token));
    if (!new_redir)
    {
        perror("Malloc Failed");
        return;
    }
    new_redir->value = ft_strdup(filename);
    if (!new_redir->value)
    {
        perror("Error");
        free(new_redir);
        return;
    }
    new_redir->type = type;
    new_redir->next = NULL;
    if (!parsing->redirections)
        parsing->redirections = new_redir;
    else
    {
        current_redir = parsing->redirections; //for the last one
        while (current_redir->next)
            current_redir = current_redir->next;
        current_redir->next = new_redir;
    }
}

void free_parasing(t_parsing    *list)
{
    t_parsing   *current_parsing;
    t_parsing   *next_parsing;
    int     i;
    
    i = 0;
    current_parsing = list;
    while (current_parsing)
    {
        next_parsing = current_parsing->next_cmd;
        if (current_parsing->argv[i])
        {
            i = 0;
            while (current_parsing->argv[i])
            {
                free (current_parsing->argv[i]);
                i++;
            }
            free(current_parsing->argv);
        }
        free_tokens(current_parsing->redirections);
        current_parsing = next_parsing;
    }
}
static int handle_pipe(t_parsing )
{
    
}


// static int handle_pipe_token(t_parsing **head, t_parsing **current_node, t_token **token)
// {
//     if (!(*current_node)->argv && !(*current_node)->redirections)
//     {
//         fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
//         free_parsing_list(*head);
//         return (1);
//     }
//     if (!(*token)->next)
//     {
//         fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
//         free_parsing_list(*head);
//         return (1);
//     }
//     (*current_node)->next_cmd = new_node();
//     if (!(*current_node)->next_cmd)
//     {
//         free_parsing_list(*head);
//         return (1);
//     }
//     *current_node = (*current_node)->next_cmd;
//     *token = (*token)->next;
//     return (0);
// }
