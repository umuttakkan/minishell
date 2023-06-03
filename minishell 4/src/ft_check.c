/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:35:57 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/05/30 21:35:58 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check(char *str)
{
    int i;
    int a;
    int b;

    i = 0;
    a = 0;
    b = 0;
    while (str[i])
    {
        if (str[i] == '>' && ((str[i + 1] == '>' && str[i + 2] == '>') || (str[i] == '|' || str[i] == '<')))
            return (0);
        else if ((str[i] == '<' && ((str[i + 1] == '<' && str[i + 2] == '<') || (str[i] == '|' || str[i] == '>'))))
            return (0);
        else if ((str[i] == '|' && ((str[i + 1] == '|') || (str[i] == '<' || str[i] == '>'))))
            return (0);
        else if (str[i] == '\'')
            a++;
        else if (str[i] == '\"')
            b++;
        i++;
    }
    if (a % 2 != 0 || b % 2 != 0)
        return (-1);
    return (1);
}

int input_check(char *str)
{
    int x;

    x = ft_check(str);
    if (x == 0)
        exit(printf("Error1\n"));
    else if(x == -1)
        exit(printf("Error2\n"));
    return(1);
}
