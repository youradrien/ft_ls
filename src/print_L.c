/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printL.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 12:50:15 by julessainthor     #+#    #+#             */
/*   Updated: 2026/06/14 12:50:16 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void print_acl_xattr(char *path)
{
    acl_t acl;
    ssize_t xattr;

    xattr = listxattr(path, NULL, 0, 0);

    if (xattr > 0)
    {
        printf("@");
        return;
    }

    acl = acl_get_file(path, ACL_TYPE_EXTENDED);
    if (acl)
    {
        acl_free(acl);
        printf("+");
        return;
    }

    printf(" ");
}

void print_l_total(char **entries, t_ls *ls, char *path)
{
    int total_blocks = 0, i = 0;
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

void print_L(char *path, char *name, int is_linkk)
{
    struct stat st;
    char *full;
    if(!is_linkk)
        full = (ft_joinpath(path, name));
    else
        full = strdup(path);

    if (lstat(full, &st) == -1)
    {
        free(full);
        return;
    }

    // type
    printf("%c", file_type(st.st_mode));
    // perms
    print_perms(st.st_mode);
    // ACL/xattr
    print_acl_xattr(full);
   
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
    if(!is_linkk)
        printf(" %s\n", (name != NULL) ? name : path);

    free(full);
}