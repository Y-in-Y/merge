/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:37:53 by ylee              #+#    #+#             */
/*   Updated: 2021/07/24 22:38:26 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    rearrange_arg(t_all *a)
{
    int     i;
    int     cnt;
    char    **new;

    i = 0;
    cnt = 0;
    while (a->arg && a->arg[i])
    {
        if (a->arg[i][0])
            cnt++;
        i++;
    }
    new = (char **)malloc(sizeof(char *) * (cnt + 1));
    i = 0;
    cnt = 0;
    while (a->arg[i])
    {
        if (a->arg[i][0] != '\0')
        {
            printf("a->arg[%d][0] : %c = %d\n", i, a->arg[i][0], a->arg[i][0]);
            new[cnt] = ft_strdup(a->arg[i]);
            cnt++;
        }
        free(a->arg[i]);
        i++;
    }
    new[cnt] = NULL;
    free(a->arg[i]);
    free(a->arg);
    a->arg = new;
    i = 0;
    while (a->arg && a->arg[i])
    {
        printf("new a->arg[%d] : %s\n", i, a->arg[i]);
        i++;
    }
}

