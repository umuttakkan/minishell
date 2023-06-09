/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:45:04 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/06/08 17:49:28 by uakkan           ###   ########.fr       */
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
	int x;

    j = 0;
	x = 0;
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

int	ft_dollar(char *data)
{
	int i;
	
	i = 0;
	while(data[i])
	{
		if (data[i] == '$' && data[i + 1] == '$')
			return (getpid());
		i++;
	}
	return (0);
}

char	*control1(char	*tmp, int x)
{
	char	*data;
	char	**str;
	int		y;
	char	*pid;

	data = ft_strdup(tmp + x / 2);
	y = ft_dollar(data);
	pid = ft_itoa(y);
	if (pid)
		return (pid);
	if (data[0] != '$' && ft_isprint(data[0]))
	{
		str = ft_split(data, '$');	
		return (str[0]);
	}
	return (NULL);
}

void	ft_tilde(char *tmp, char *str, t_list *data)
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
	(data)->content = ft_strjoin(str1,tmp);
	printf("%s", data->content);
}
int	dollar(char *tmp)
{
	int i;
	int	x;

	x = 0;
	i = 0;
	while(tmp[i])
	{
		if (tmp[i] == '$')
			x++;
		i++;
	}
	return (x);
}
int check_env(t_list *data, char *tmp, int x)
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
	a = dollar(tmp);
    while (shell_data)
    {
        y = shell_data->content;
		if (tmp[0] == '~' && (ft_strcmp (y->key,"PWD") == 0))
			ft_tilde(tmp,y->value, data);
        if(ft_ultimatestrcmp(y->key, tmp, 0) && (a % 2 != 0))
        {
			str = y->value;
			if (str1)
				(data)->content = ft_strjoin(str1, str);
			else
			 	(data)->content = str;
			printf("%s\n", data->content);
        }
		if (a % 2 == 0)
		{
			data->content = ft_strjoin(str1, tmp + a);
			printf("%s\n", data->content);
			break ;
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

void	get_env_to_lexlist(t_lexer **lex_list)
{
    int		i;
	int		x;
	int		a;
    t_list	*data;
	char	*tmp;
	char	**str;
	int		cont;

    data = (*lex_list)->lex;
	cont = 1;
    while (data)
    {
		i = 0;
	    tmp = (char *)data->content;
		a = quote_len(tmp);
		if (a > 0)
		 	tmp = control2(tmp);
		x = control(tmp);
        while (tmp[i])
        {
			if(tmp[i] == '~' && tmp[i - 1] != '~' && tmp[i + 1] != '~' && cont++ == 1)
				check_env(data, tmp, x);
			if (tmp[i - 1] != 92 && tmp[i] == 92 && tmp[i + 1] == '$')
            {
				str = ft_split((data)->content, 92);
				(data)->content = double_to_single(str);
            }
            else if (tmp[i] == '$' && x >= 0)
            {
				check_env(data, tmp, x);
				break ;
            }
			i++;
        }
		(data) = (data)->next;
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
	get_env_to_lexlist(&(g_shell->lex_list));
	if(ft_strcmp(g_shell->lex_list->lex->content, "env") == 0 || 
		ft_strcmp(g_shell->lex_list->lex->content, "ENV") == 0)
		ft_lstiter((g_shell)->env, &print_list);
}