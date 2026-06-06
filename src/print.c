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

// static void print_perms(mode_t mode)
// {
//     printf("%c", (mode & S_IRUSR) ? 'r' : '-');
//     printf("%c", (mode & S_IWUSR) ? 'w' : '-');
//     printf("%c", (mode & S_IXUSR) ? 'x' : '-');

//     printf("%c", (mode & S_IRGRP) ? 'r' : '-');
//     printf("%c", (mode & S_IWGRP) ? 'w' : '-');
//     printf("%c", (mode & S_IXGRP) ? 'x' : '-');

//     printf("%c", (mode & S_IROTH) ? 'r' : '-');
//     printf("%c", (mode & S_IWOTH) ? 'w' : '-');
//     printf("%c", (mode & S_IXOTH) ? 'x' : '-');
// }

static char file_type(mode_t mode)
{
    if (S_ISREG(mode)) return '-';
    if (S_ISDIR(mode)) return 'd';
    if (S_ISLNK(mode)) return 'l';
    if (S_ISCHR(mode)) return 'c';
    if (S_ISBLK(mode)) return 'b';
    if (S_ISFIFO(mode)) return 'p';
    if (S_ISSOCK(mode)) return 's';
    return '?';
}

static void print_perms(mode_t mode)
{
    // USER
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');

    if (mode & S_ISUID)
        printf("%c", (mode & S_IXUSR) ? 's' : 'S');
    else
        printf("%c", (mode & S_IXUSR) ? 'x' : '-');

    // GROUP
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');

    if (mode & S_ISGID)
        printf("%c", (mode & S_IXGRP) ? 's' : 'S');
    else
        printf("%c", (mode & S_IXGRP) ? 'x' : '-');

    // OTHER
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');

    if (mode & S_ISVTX)
        printf("%c", (mode & S_IXOTH) ? 't' : 'T');
    else
        printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}


void print_L(char *path, char *name)
{
    struct stat st;
    char *full = ft_joinpath(path, name);

    if (lstat(full, &st) == -1)
    {
        free(full);
        return;
    }
    //printf("%s vs %s \n", path, name);
    // type
    printf("%c", file_type(st.st_mode));
    // perms
    print_perms(st.st_mode);
    // links
    printf(" %lu", (unsigned long)st.st_nlink);

    // owner / group
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);
    // size
    printf(" %lld", (long long)st.st_size);
    // time
    char *t = ctime(&st.st_mtime);
    printf(" %.12s", t + 4);
    // name
    printf(" %s\n", (name != NULL) ? name : path);

    free(full);
}


void print_files(char **entries, t_ls *ls, char *path)
{
    int i = 0;
    int total_blocks = 0;
    if(ls->options.l)
    {
        struct stat st;
        while (entries && entries[i])
        {
            char *full = ft_joinpath(path, entries[i]);
            if (lstat(full, &st) == -1 || (entries[i][0] == '.' && !ls->options.a))
            {
                free(full);
                i++;
                continue;
            }
            total_blocks += st.st_blocks;
            free(full);
            i++;
        }
        printf("total %d\n", total_blocks);
    }
    i = 0;
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
}

