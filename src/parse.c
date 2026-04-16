/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:04:51 by julessainthor     #+#    #+#             */
/*   Updated: 2026/04/16 14:04:52 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"


    static char **read_dir(char *path, int *minimum_dirs)
    {
        DIR *dir;

        dir = opendir(path);
        if (!dir)
            return NULL;

        // 1. count
        struct dirent *entry;
        int count = 0;
        while ((entry = readdir(dir)))
            count++;

        *minimum_dirs = (count);
        closedir(dir);

        // 2. fill
        dir = opendir(path);
        int i = 0;

        char **entries = (char **) malloc(sizeof(char *) * (count + 1));
        while ((entry = readdir(dir)))
        {
            if (ft_strcmp(entry->d_name, ".") == 0
            || ft_strcmp(entry->d_name, "..") == 0)
                continue;

            entries[i++] = strdup(entry->d_name);
        }

        entries[i] = NULL;
        closedir(dir);
        return entries;
    }

static char **extract_dirs(char **entries, int minimum_dirs)
{
    struct stat st;
    char    **dirs;
    int i = 0, 
        j = 0;

    dirs = malloc(sizeof(char *) * (minimum_dirs + 1));
    if (!dirs)
        return NULL;

    // 2. fill
    i = 0;
    while (entries[i])
    {
        if (stat(entries[i], &st) == 0 && S_ISDIR(st.st_mode))
            dirs[j++] = entries[i];
        i++;
    }

    dirs[j] = NULL;
    return dirs;
}

void list_dir(char *path, t_opts *opts)
{
    char **entries;
    int min_dirs;

    entries = read_dir(path, &min_dirs);
    // sort(entries, opts);

    print_files(entries);

    if (opts->R)
    {
        printf("-R oof \n");
        char **dirs = extract_dirs(entries, min_dirs);
        // for each dir:
        int i = 0;
        while(dirs[i])
        {
            printf("dirs[%d] = %s \n",i, dirs[i]);
            char *full = ft_joinpath(path, dirs[i]);
            list_dir(full, opts);
            free(full);
            i++;
            return;
        }
    }
}



static int parse_flags(char *arg, t_opts *opts)
{
    int i = 1;
    while (arg[i])
    {
        if (arg[i] == 'l') opts->l = 1;
        else if (arg[i] == 'R') opts->R = 1;
        else if (arg[i] == 'a') opts->a = 1;
        else if (arg[i] == 'r') opts->r = 1;
        else if (arg[i] == 't') opts->t = 1;
        else
        {
            write(1, "ft_ls: illegal flag option -- ", 30);
            write(1, &arg[i], 1);
            write(1, "\n", 1);
            return (1);
        }
        i++;
    }
    return (0);
}

int parse_args(int argc, char **argv, t_ls *ls)
{
	int i = 1, c = 0;
	
	ls->paths = (char **) malloc((sizeof(char *)) * (argc + 1));
	if (!ls->paths)
		return (0);
 	while (i < argc)
    {
        // case:"--"
        if (strcmp(argv[i], "--") == 0)
        {
            i++;
            while (i < argc)
                ls->paths[c++] = argv[i++];
            break;
        }
        // flags
        else if (argv[i][0] == '-' && argv[i][1])
        {
            if (parse_flags(argv[i], &ls->options))
                return (0);
        }
        // paths
        else
        {
            ls->paths[c++] = argv[i];
        }
        i++;
    }
    ls->paths[c] = NULL;
    c = 0;
    while(ls->paths[c]){
        list_dir(ls->paths[c], &(ls->options));
        c++;
    }
	// split_files_dirs(ls, c);
    return (1);
}
