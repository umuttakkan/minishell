/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:36:01 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/01 21:25:57 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_len(char *data)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
			j++;
		i++;
	}
	return (j);
}

char	*cmd_build(char *cmd)
{
	int		len;
	int		i;
	int 	a;

	i = -1;
	len = quote_len(cmd);
	while (cmd[++i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			a = cmd[i];
			while(len > 0)
			{
				if (cmd[i++] == a)
				{
					len--;
					if(len % 2 == 0)
						break ;
				}
			}
		}
		if (cmd[i] == ' ')
			cmd[i] = 2;
	}
	return (cmd);
}

void lex_list(char *cmd, t_lexer **lex_table)
{
    char    **str;
    char    *data;
    int     i;
    int     control;
    t_list  *new_node;

    i = 0;
    control = 0;
    data = cmd_build(cmd);
    str = ft_split(data, 2);
    if (!str)
        return;
    while (str[i])
    {
        new_node = ft_lstnew(ft_strdup(str[i]));
        if (control == 0)
        {
            (*lex_table)->lex = new_node;
            control = 1;
        }
        else
            ft_lstadd_back(&(*lex_table)->lex, new_node);
        i++;
	}
}

void lexer(void)
{
    lex_list(g_shell->cmd->read_data, &(g_shell->lex_list));
	// while (g_shell->lex_list->lex)
	// {
    // 	printf("content = %s\n", (char *)g_shell->lex_list->lex->content);
	// 	g_shell->lex_list->lex = g_shell->lex_list->lex->next;
	// }
}
