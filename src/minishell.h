/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:18 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/08 15:31:17 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"


typedef struct s_env
{
    char *key;
    char *value;
}              t_env;

typedef struct s_data
{
	char *read_data;
}				t_data;

typedef struct s_lexer
{
    t_list *lex;
}              t_lexer;

typedef struct s_shell
{
	t_list	*env;
    t_data  *cmd;
    t_lexer *lex_list;
}               t_shell;

t_shell *g_shell;

void		signals(int sig);
void		env_get(char **env, t_shell **shell);
void        get_readline(t_data *b);
int         ft_check(char *str);
int         input_check(char *str);
void        lexer(void);
void        expander(void);
void        get_env_to_lexlist(t_lexer **lex_list);
int         check_env(t_list *data, char *tmp, int x);
int			ft_ultimatestrcmp(char *key, char *tmp, int i);
char	    *control1(char	*tmp, int x);
int			ft_dollar(char *data);
int			quote_len(char *data);

#endif