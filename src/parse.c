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


static void sort_paths(t_ls *ls)
{
    int i, j;
    char *tmp;
    char **_files;
    char **_dirs;
    
    _files = (char **)(malloc(sizeof(char *) * ls->path_len));
    _dirs = (char **)(malloc(sizeof(char *) * ls->path_len));
    if(!_files || !_dirs)
        return ; 
    int a = 0, b = 0;

    // split files/dirs
    for (i = 0; ls->paths[i]; i++)
    {
        struct stat st;
        if (stat(ls->paths[i], &st) == 0)
        {
            if (S_ISDIR(st.st_mode))
                _dirs[a++] = ls->paths[i];
                // dossier
            else
                // fichier
                _files[b++] = ls->paths[i];
        }else
            perror(ls->paths[i]);
    }
    _dirs[a] = NULL;
    _files[b] = NULL;

    // sort both
    for(int k = 0; k < 2; k ++)
    {
        char * **z[2] = {&(_files), &(_dirs)};
        char **arr = *z[k];
        for (i = 0; arr[i]; i++)
        {
            for (j = i + 1; arr[j]; j++)
            {
                int cmp = strcmp(arr[i], arr[j]);

                if (ls->options.r)
                    cmp = -cmp;
                if (cmp > 0)
                {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }
    a = 0;
    for(int k = 0; k < 2; k ++)
    {
        char * **z[2] = {&(_files), &(_dirs)};
        char **arr = *z[k];
        printf("%s: \n", k == 0 ? "files" : "dirs");
        int i = 0;
        while(arr[i]){
            printf("- %s\n", arr[i]);
            ls->paths[a] = arr[i];
            i++;
            a++;
        }
    }
    printf("ls->paths\n");
    for(int i = 0; i <= ls->path_len; i++)
    {
        printf("- %s\n", ls->paths[i]);
    }
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
    ls->path_len = (c);
    sort_paths(ls);
    return (1);
}
