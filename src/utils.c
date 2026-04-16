/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:12:16 by julessainthor     #+#    #+#             */
/*   Updated: 2026/04/16 12:12:16 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char *ft_joinpath(char *path, char *name)
{
    char *tmp;
    char *res;

    tmp = ft_strjoin(path, "/");
    res = ft_strjoin(tmp, name);
    free(tmp);
    return res;
}


int cmp_alpha(char *a, char *b)
{
    return strcmp(a, b);
}

int cmp_time(char *a, char *b, char *path)
{
    struct stat st1, st2;
    char *p1 = ft_joinpath(path, a);
    char *p2 = ft_joinpath(path, b);

    stat(p1, &st1);
    stat(p2, &st2);

    free(p1);
    free(p2);

    if (st1.st_mtime == st2.st_mtime)
        return strcmp(a, b);

    return (st2.st_mtime - st1.st_mtime);
}
