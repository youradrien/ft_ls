/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:01:36 by julessainthor     #+#    #+#             */
/*   Updated: 2026/04/16 14:01:37 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_files(char **entries, t_ls *ls)
{
    int i = 0;
    
    while (entries && entries[i])
    {
        if (entries[i][0] == '.' && 
            !ls->options.a)
        {
            // fichier caché
            i++;
            continue;
        }
        printf("%s\t", entries[i]);
        i++;
    }
    printf("\n\n");
}

