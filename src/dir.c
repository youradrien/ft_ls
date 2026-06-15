/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:35:28 by julessainthor     #+#    #+#             */
/*   Updated: 2026/04/21 18:35:29 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void sort(char **entries, t_opts *opts, char *path)
{
    int i, j;
    char *tmp;

    for (i = 0; entries[i]; i++)
    {
        for (j = i + 1; entries[j]; j++)
        {
            int cmp;
            if (opts->t)
                cmp = cmp_time(entries[i], entries[j], path);
            else
                cmp = strcmp(entries[i], entries[j]);

            if (opts->r)
                cmp = -cmp;
            if (cmp > 0)
            {
                tmp = entries[i];
                entries[i] = entries[j];
                entries[j] = tmp;
            }
        }
    }
}




static char **read_dir(char *path, int *minimum_dirs, t_opts *opts)
{
    DIR *dir;

    dir = opendir(path);
    if (!dir)
    {
        printf("ft_ls: %s: Permission denied\n", path);
        return NULL;
    }

    // 1. count
    struct dirent *entry;
    int c = 0;
    while ((entry = readdir(dir)))
        c++;

    *minimum_dirs = (c);
    closedir(dir);

    // 2. fill
    dir = opendir(path);
    int i = 0;

    char **entries = (char **) malloc(sizeof(char *) * (c + 1));
    while ((entry = readdir(dir)))
    {
        if ((!opts->a) && (ft_strcmp(entry->d_name, ".") == 0
            || ft_strcmp(entry->d_name, "..") == 0)
        )
            continue;

        // printf("entry[%d]: %s \n", i, entry->d_name);   
        entries[i++] = strdup(entry->d_name);
    }

    entries[i] = NULL;
    closedir(dir);
    return entries;
}




static char **extract_dirs(char **entries, int minimum_dirs, char *path)
{
    struct stat st;
    char    **dirs;
    int i = 0, 
        j = 0;

    dirs = malloc(sizeof(char *) * (minimum_dirs + 1));
    if (!dirs)
        return NULL;

    i = 0;
    while (entries[i])
    {
        char *a = ft_joinpath(path, entries[i]);
        if (stat(a, &st) == 0 && S_ISDIR(st.st_mode))
            dirs[j++] = entries[i];
        free(a);
        i++;
    }

    dirs[j] = NULL;
    return dirs;
}



static  int is_a_file(char *path, t_ls *ls, int i)
{
    struct stat st;
    if (stat(path, &st) == -1)
    {
        // perror(path);
        return 1;
    }
    if (!S_ISDIR(st.st_mode)) // fichier → pas opendir
    {
        if(ls->options.l)
            print_L(path, NULL, 0);
        else
            printf("%s\t", path);
        if(ls->path_nb_dirs > 0)
        {
            if(i == ls->path_nb_files)
                printf("\n\n");
        }
        return 1;
    }
    return 0;
}




static int is_a_symlink(char *path, t_ls *ls)
{
    struct stat st;

    if (lstat(path, &st) == -1)
        return 1;

    if (S_ISLNK(st.st_mode))
    {
        // printf("path: %s \n", path);
        if(ls->options.l){
            print_L(path, "", 1);
        }
        // symlink
        char buf[PATH_MAX];
        ssize_t len = readlink(path, buf, sizeof(buf) - 1);

        printf(" %s", path);
        if (len != -1)
        {
            buf[len] = '\0';
            printf(" -> %s", buf);
        }
        printf("\n");
        return 1;
    }else
        return 0;
}





void list_dir(char *path, t_opts *opts, t_ls *ls, int i, int first_recursiv__call)
{
    char **entries;
    int min_dirs;

    // link
    if(is_a_symlink(path, ls)){
        return ;
    }
    // file
    if(is_a_file(path, ls, i)){
        return;
    }

    entries = read_dir(path, &min_dirs, opts);
    if (!entries)
        return;
    
    sort(entries, opts, path);

    // directory
    char **dirs = extract_dirs(entries, min_dirs, path);
    if( (!opts->R && ls->path_len > 1)
        || (opts->R))
    {
        printf("%s: \n", path);
    }

        
    print_files(entries, ls, path);
    
    if((i != (ls->path_nb_dirs + ls->path_nb_files) && ls->path_nb_dirs > 1)
        || (opts->R))
    {
        printf(entries[0] ? "\n\n" : "\n");
    }

    // -R flag
    if (opts->R)
    {
        // for-each dir
        int i = 0;
        while(dirs[i])
        {
            if (strcmp(dirs[i], ".") == 0 || strcmp(dirs[i], "..") == 0){
                i++;
                continue;
            }
            char *full = ft_joinpath(path, dirs[i]);
            if( (opts->a && dirs[i][0] == '.') || dirs[i][0] != '.')
            {
                // recursive call
                list_dir(full, opts, ls, i, first_recursiv__call + 1);
            }
            free(full);
            i++;
        }
    }
}

