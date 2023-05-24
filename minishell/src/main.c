/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:07:54 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/05/23 19:01:59 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shell_init(t_shell **shell)
{
    *shell = malloc(sizeof(t_shell *));
	(*shell)->env = malloc(sizeof(t_env *));
    (*shell)->env->key = NULL;
    (*shell)->env->value = NULL;
}

int main(int ac, char **av, char **env)
{
    t_shell *shell;
    char *a;
    (void)av;
    (void)env;
	
	shell = NULL;
    shell_init(&shell);
    if (ac != 1)
        exit(printf("This program cannot accept any arguments\n"));
 	env_get(env, &shell);
	exit(1);
    signal(SIGINT, signals);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        a = readline("Minishell > ");
        if (!a)
           signals(3);

    }
}