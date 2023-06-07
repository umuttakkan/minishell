/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:45:04 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/06 20:19:20 by uakkan           ###   ########.fr       */
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

char *ft_dollar(char *data)
{
	int i;

	i = 0;
	while(data[i])
	{
		if (data[i] == '$')
			return (&data[i + 1]);
		i++;
	}
	return (NULL);
}

char	*control1(char	*tmp, int x)
{
	char	*data;
	char	**str;

	data = ft_strdup(tmp + x / 2);
	tmp = ft_dollar(data);
	str = ft_split(data, '$');	
	return (str[0]);
}

void	ft_tilde(char *tmp, char *str, t_lexer **data)
{
	int		i;
	int		j;
	int		x;
	char	*str1;

	i = 0;
	j = 0;
	x = 0;
	str1 = malloc(sizeof(char *) + ft_strlen(str));
	tmp = ft_strchr(tmp, '/');
	tmp = tmp + 1;
	while(str[i] && j < 3)
	{
		str1[x] = str[i];
		if (str[i] == '/')
			j++;
		i++;
		x++;
	}
	(*data)->lex->content =	ft_strjoin(str1,tmp);
	printf("%s", (*data)->lex->content);
}

int check_env(t_lexer **data, char *tmp, int x)
{
    t_env	*y;
    t_shell *shell;
	t_list	*shell_data;
    int		a;
	char	*str;
	char	*str1;
	
    shell = g_shell;
	shell_data = shell->env;
	str1 = control1(tmp, x);
    while (shell_data)
    {
        y = shell_data->content;
		if (tmp[0] == '~' && (ft_strcmp (y->key,"PWD") == 0))
			ft_tilde(tmp,y->value, data);
        a = ft_ultimatestrcmp(y->key, tmp, 0);
        if(a)
        {
			str = y->value;
			if (x > 0)
				(*data)->lex->content = ft_strjoin(str1, str);
			else 
				(*data)->lex->content = str;
			printf("%s\n", (*data)->lex->content);
        }
		shell_data = shell_data->next;
    }
    return (0);
}

int	control(char *tmp)
{
	int	i;
	int x;

	x = 0;
	i = 0;
	while(tmp[i])
	{
		if (tmp[i] == 92)
			x++;
		i++;
	}
	if (x / 2 >= 0)
		return (x);
	return (0);
}

char	*control2(char *tmp)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char *) + ft_strlen(tmp));
	while(tmp[i])
	{
		while(tmp[i] && tmp[i] == '\"')
			i++;
		while(tmp[i] && tmp[i] != '\"')
		{
			str[j] = tmp[i];
			j++;
			i++;
		}
		i++;
	}
	return (str);
}
int	tilda_len(char *tmp)
{
	int i;
	int	j;

	j = 0;
	i = 0;
	while(tmp[i])
	{
		if (tmp[i] == '~')
			j++;
		i++;
	}
	if (j == 1)
		return (j);
	return (0);
}

void	get_env_to_lexlist(t_lexer **lex_list)
{
    int		i;
	int		x;
	int		a;
    t_lexer	**data;
	char	*tmp;
	char	**str;

    data = lex_list;
    while ((*data)->lex)
    {
		i = 0;
	    tmp = (char *)(*data)->lex->content;
		a = quote_len(tmp);
		if (a > 0 && !ft_strchr(tmp, '\"') && !ft_strchr(tmp, '\''))
		 	tmp = control2(tmp);
		x = control(tmp);
        while (tmp[i])
        {
			if(tmp[i] == '~' && tilda_len(tmp) == 1) //&& !ft_strchr(tmp, '\"') && !ft_strchr(tmp, '\''))
				check_env(data, tmp, x);
            if (tmp[i - 1] != 92 && tmp[i] == 92 && tmp[i + 1] == '$')
            {
				str = ft_split((*data)->lex->content, 92);
				(*data)->lex->content = double_to_single(str);
			    // printf("%s", (char *)(*lex_list)->lex->content);            
            }
            else if (tmp[i] == '$' && x >= 0)
            {
                if (x == 0)
                    check_env(data, tmp + 1, x);
                else if (x % 2 == 0)
                    check_env(data, tmp, x);
            }
			i++;
        }
		(*data)->lex = (*data)->lex->next;
		free(tmp);
    }
}

void	print_list(void *data)
{
	t_env *new;

	new = (t_env*)data;
	printf("%s", new->key);
	printf("=");
	printf("%s\n", new->value);
}

void expander(void)
{
	if(ft_strcmp(g_shell->lex_list->lex->content, "env") == 0 || 
		ft_strcmp(g_shell->lex_list->lex->content, "ENV") == 0)
		ft_lstiter((g_shell)->env, &print_list);
	get_env_to_lexlist(&(g_shell->lex_list));
}