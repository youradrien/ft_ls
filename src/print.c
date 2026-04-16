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

void print_files(t_ls *ls)
{
    int i = 0;

    while (ls->files && ls->files[i])
    {
        printf("%s\n", ls->files[i]);
        i++;
    }
}

void print_dir_content(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (!dir)
        return;
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] == '.')
            continue;
        printf("%s\t", entry->d_name);
    }
    closedir(dir);
}

void print_dirs(t_ls *ls)
{
    int i = 0;

    while (ls->dirs && ls->dirs[i])
    {
        printf("\n%s:\n", ls->dirs[i]);
        print_dir_content(ls->dirs[i]); // sans récursion globale
        printf("\n");
        i++;
    }
}

