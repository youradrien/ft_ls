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

static inline int init_ls(t_ls *ls)
{
    ls->options.l = 0;
    ls->options.R = 0;
    ls->options.a = 0;
    ls->options.r = 0;
    ls->options.t = 0;
	return 0;
}

int main(int argc, char **argv)
{
	t_ls *ls;

	ls = (t_ls *) malloc(sizeof(t_ls));
	if(!ls || init_ls(ls) || !parse_args(argc, argv, ls))
	{
		return (1);
	}
	if (!ls->paths || !ls->paths[0])
	{
		list_dir(".", &ls->options, ls, 0, 0);
	}
	else
	{
		// printf("pathlen: %d \npath->nb_files: %d\npath->nb-dirs: %d \n", 
		// 		ls->path_len, ls->path_nb_files, ls->path_nb_dirs
		// );
		int i = 0;
		while (ls->paths[i])
		{
			list_dir(ls->paths[i++], &ls->options, ls, i, 0);
		}
	}
	free(ls);
	// test debug
    // printf("options: l=%d R=%d a=%d r=%d t=%d\n",
    //     ls->options.l,
    //     ls->options.R,
    //     ls->options.a,
    //     ls->options.r,
    //     ls->options.t);
	return (0);
}
