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

static int max_name_len(char **entries, t_ls *ls)
{
    int i = 0, max = 0, len;

    while (entries && entries[i])
    {
        if (entries[i][0] == '.' && !ls->options.a)
        {
            i++;
            continue;
        }
        len = strlen(entries[i]);
        if (len > max)
            max = len;
        i++;
    }
    return (max);
}


static int visible_count(char **entries, t_ls *ls)
{
    int i = 0, count = 0;
    while (entries && entries[i])
    {
        if (!(entries[i][0] == '.' && !ls->options.a))
            count++;
        i++;
    }
    return (count);
}



static char **visible_entries(char **entries, t_ls *ls)
{
    int i, j, count;
    char **tab;

    count = visible_count(entries, ls);
    tab = malloc(sizeof(char *) * (count + 1));
    if (!tab)
        return (NULL);

    i = 0, j = 0;
    while (entries && entries[i])
    {
        if (!(entries[i][0] == '.' && !ls->options.a))
            tab[j++] = entries[i];
        i++;
    }
    tab[j] = NULL;
    return (tab);
}



static void print_columns(char **entries, t_ls *ls)
{
    char **tab;
    int width, cols, rows, count;

    tab = visible_entries(entries, ls);
    if (!tab)
        return ;

    count = visible_count(entries, ls);
    width = max_name_len(tab, ls) + 2;

    cols = get_term_width() / width;
    if (cols < 1)
        cols = 1;

    rows = (count + cols - 1) / cols;

    // printf("rows: %d\t cols: %d\n", rows, cols);
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            int idx = r + c * rows;
            if (idx < count)
                printf("%-*s", width, tab[idx]);

            c++;
        }
        printf("\n");
        r++;
    }

    free(tab);
}


// [main print entry]
void print_files(char **entries, t_ls *ls, char *path)
{
    int i = 0;

    if(ls->options.l)
    {
        print_l_total(entries, ls, path);
        while (entries && entries[i])
        {
            if (entries[i][0] == '.' && 
                !ls->options.a)
            {
                // fichier caché
                i++;
                continue;
            }

            print_L(path, entries[i], 0);
            i++;
        }
        printf("\n");
    }else
    {
        print_columns(entries, ls);
    }

}

