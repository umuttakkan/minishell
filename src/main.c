/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:07:54 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/08 18:24:21 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shell_init(t_shell **shell)
{
    *shell = malloc(sizeof(t_shell *));
	(*shell)->env = malloc(sizeof(t_list *));
    (*shell)->env->content = NULL;
    (*shell)->env->next = NULL;
    (*shell)->lex_list = malloc(sizeof(t_lexer *));
    (*shell)->lex_list->lex = NULL;
}

void get_readline(t_data *b)
{
    b->read_data = readline("Minishell >");
    if (!b->read_data)
        exit(1);
    add_history(b->read_data); 
}

int main(int ac, char **av, char **env)
{
    (void)av;
    (void)env;

    shell_init(&g_shell);
    if (ac != 1)
    	exit(printf("This program cannot accept any arguments\n"));
    g_shell->cmd = malloc(sizeof(t_data));
 	env_get(env, &g_shell);
    signal(SIGINT, signals);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    { 
        get_readline(g_shell->cmd);
        if (input_check(g_shell->cmd->read_data))
        {   
            lexer();
            // expander();
        }
    }
}