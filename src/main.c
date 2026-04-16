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

int main(int argc, char **argv)
{
	t_ls *ls;

	ls = (t_ls *) malloc(sizeof(t_ls));
	if(!ls || !parse_args(argc, argv, ls))
	{
		return (1);
	}
	// test debug
    // printf("options: l=%d R=%d a=%d r=%d t=%d\n",
    //     ls->options.l,
    //     ls->options.R,
    //     ls->options.a,
    //     ls->options.r,
    //     ls->options.t);
	// int i = 0;
    // while (ls->paths[i])
    // {
    //     printf("path: %s\n", ls->paths[i]);
    //     i++;
    // }
	return (0);
}
