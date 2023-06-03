/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:16 by uakkan            #+#    #+#             */
/*   Updated: 2023/06/01 20:47:57 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_str(char **str)
{		
		free(str[0]);
		free(str[1]);
		free(str);
}

// void	print_list(void *data)
// {
// 	t_env *new;

// 	new = (t_env*)data;
// 	printf("%s", new->key);
// 	//printf("%s", new->value);
// }

// void	free_list(void *data)
// {
// 	t_env *new;

// 	new = (t_env*)data;
// 	free(new->key);
// 	free(new->value);
// 	free(new);
// }

void	env_get(char **env, t_shell **shell)
{
	t_env	*a;
	char	**str;	
	
	a = NULL;
	while(*env)
	{
		str = ft_split(*env, '=');
		a = malloc(sizeof(t_env));
		a->key = ft_strdup(str[0]);
		a->value = ft_strdup(str[1]);
		if ((*shell)->env->content == NULL)
			(*shell)->env->content = a;
		else
			ft_lstadd_back(&(*shell)->env, ft_lstnew(a));
		free_str(str);
		env++;
	}
	(*shell)->env = (*shell)->env->next;
	// ft_lstiter((*shell)->env, &print_list);
	// ft_lstiter((*shell)->env, &free_list);
}



// void	env_get(char **env, t_shell **shell)
// {
// 	t_env *tmp;
// 	char **str;

// 	tmp = NULL;
// 	while (*env)
// 	{
// 		str = ft_split(*env, '=');
// 		if (tmp == NULL)
// 		{
// 			(*shell)->env = malloc(sizeof(t_env));
// 			(*shell)->env->key = NULL;
//    			(*shell)->env->value = NULL;
// 			tmp = (*shell)->env;
// 		}
// 		else
// 		{
// 			tmp->next = malloc(sizeof(t_env));
// 			tmp = tmp->next;
// 		}
// 		tmp->key = ft_strdup(str[0]);
// 		tmp->value = ft_strdup(str[1]);
// 		tmp->next = NULL;
// 		free_str(str);
// 		env++;
// 	}
// }
// 	while ((*shell)->env != NULL)
// 	{
// 		printf("%s\n", (*shell)->env->value);
// 		(*shell)->env = (*shell)->env->next;
// 	}


// void env_get(char **env, t_shell **shell)
// {
// 	t_env *tmp;
// 	t_env *new_env;
// 	char **str;

// 	tmp = NULL;
// 	while (*env)
// 	{
// 		str = ft_split(*env, '=');
// 		new_env = malloc(sizeof(t_env));
// 		new_env->key = ft_strdup(str[0]);
// 		new_env->value = ft_strdup(str[1]);
// 		new_env->next = NULL;

// 		if (tmp == NULL)
// 		{
// 			// free((*shell)->env);
// 			(*shell)->env = new_env;
// 			tmp = new_env;
// 		}
// 		else
// 		{
// 			tmp->next = new_env;
// 			tmp = tmp->next;
// 		}
// 		tmp->next = NULL;
// 		free(str[0]);
// 		free(str[1]);
// 		free(str);
// 		env++;
// 	}

// 	tmp = (*shell)->env;
// 	while ((*shell)->env != NULL)
// 	{
// 		printf("%s\n", (*shell)->env->value);
// 		free((*shell)->env->value);
// 		free((*shell)->env->key);
// 		free((*shell)->env);
// 		(*shell)->env = (*shell)->env->next;
// 	}
// 	free((*shell));
// }

