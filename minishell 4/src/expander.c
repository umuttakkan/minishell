/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:45:04 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/04 00:49:46 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *double_to_single(char **str)
{
    int i;
    int j;
    int a;
    char *data;

    i = 0;
    j = 0;
    a = 0;
	if (str[1] == NULL)
		data = malloc(sizeof(char *) + ft_strlen(str[0]) + 1);
	else
		data = malloc(sizeof(char *) + ft_strlen(str[0]) + ft_strlen(str[1]) + 1);
    while (str[i])
    {
        while (str[i][j])
        {
            data[a] = str[i][j];
            j++;
            a++;   
        }   
        i++;
    }
    return (data);
}

int ft_ultimatestrcmp(char *key, char *tmp, int i)
{
    int j;

    j = 0;
    while (tmp[i])
    {
        j = 0;
        while (tmp[i] == key[j])
        {
            i++;
            j++;
            if (!tmp[j])
                return (1);
        }  
        i++;
	}
    return (0);
}

// void take_env()
// {
//     printf("girdi girdi\n");
// }

int check_env(t_lexer **data, char *tmp)
{
    t_env	*x;
    t_shell *shell;
	t_list	*shell_data;
    int		a;
	char	*str;
	
    shell = g_shell;
	shell_data = shell->env;
    while (shell_data)
    {
        x = shell_data->content;
        a = ft_ultimatestrcmp(x->key, tmp, 0);
        if(a)
        {
			str = x->value;
			(*data)->lex->content = str;
			printf("%s\n", (char *)(*data)->lex->content);
        }
		shell_data = shell_data->next;
    }
    return (0);
}

void get_env_to_lexlist(t_lexer **lex_list)
{
    int		i;
    t_lexer	**data;
	char	*tmp;
	char	**str;

    i = 0;
    data = lex_list;
    while ((*data)->lex)
    {
	    tmp = (char *)(*data)->lex->content;
		i = 0;
        while (tmp[i])
        {
            if (tmp[i - 1] != 92 && tmp[i] == 92 && tmp[i + 1] == '$')
            {
				str = ft_split((*data)->lex->content, 92);
				(*data)->lex->content = double_to_single(str);
			    // printf("%s", (char *)(*lex_list)->lex->content);            
            }
            else if (tmp[i] == '$' && tmp[0] != '\'')
                check_env(data, tmp + 1);
			i++;
        }
		(*data)->lex = (*data)->lex->next;
		free(tmp);
    }
}

void expander(void)
{
    get_env_to_lexlist(&(g_shell->lex_list));
}