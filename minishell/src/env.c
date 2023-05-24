/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:16 by uakkan            #+#    #+#             */
/*   Updated: 2023/05/23 19:28:22 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_get(char **env, t_shell **shell)
{   
	t_env	*tmp;
	char	**str;

	tmp = (*shell)->env;
	while (*env)
	{
		str = ft_split(*env, '=');
		tmp->key = ft_strdup(str[0]);
		tmp->value = ft_strdup(str[1]); 
		tmp->next = malloc(sizeof(t_env *));
		tmp= tmp->next;
		free(str);
		env++;
	}
}
