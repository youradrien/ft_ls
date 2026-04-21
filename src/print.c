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

static void print_perms(mode_t mode)
{
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');

    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');

    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}


static void print_L(char *path, char *name)
{
    struct stat st;
    char *full = ft_joinpath(path, name);

    if (stat(full, &st) == -1)
    {
        free(full);
        return;
    }

    // type
    printf("%c", S_ISDIR(st.st_mode) ? 'd' : '-');
    // perms
    print_perms(st.st_mode);
    // links
    printf(" %lu", (unsigned long)st.st_nlink);

    // owner / group
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    // size
    printf(" %lld", st.st_size);

    // time
    char *t = ctime(&st.st_mtime);
    printf(" %.12s", t + 4);

    // name
    printf(" %s\n", name);

    free(full);
}


void print_files(char **entries, t_ls *ls, char *path)
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
        if (ls->options.l)
            print_L(path, entries[i]);
        else
            printf("%s\t", entries[i]);
        i++;
    }
    printf("\n\n");
}

