/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:12:26 by julessainthor     #+#    #+#             */
/*   Updated: 2026/04/16 12:13:04 by julessainthor    ###   ########.fr       */
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

static int parse_args(int argc, char **argv, t_ls *ls)
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
    return (1);
}

int main(int argc, char **argv)
{
	t_ls *ls;

	ls = (t_ls *) malloc(sizeof(t_ls));
	if(!ls || !parse_args(argc, argv, ls))
	{
		return (1);
	}
	// test debug
    printf("options: l=%d R=%d a=%d r=%d t=%d\n",
        ls->options.l,
        ls->options.R,
        ls->options.a,
        ls->options.r,
        ls->options.t);
	int i = 0;
    while (ls->paths[i])
    {
        printf("path: %s\n", ls->paths[i]);
        i++;
    }
	return (0);
}
