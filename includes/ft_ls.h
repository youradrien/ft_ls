
#ifndef FT_LS_H
#define FT_LS_H

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

// ls -options flags
typedef struct s_opts {
    int l,
        R,
        a,
        r,
        t;
} t_opts;


// ls whole struct
typedef struct s_ls {
    char    **paths;
    int     path_len;
    int     path_nb_files,
            path_nb_dirs;

    // files/dirs
    char    **files;
    char    **dirs;
    t_opts  options;
} t_ls;

// parse
int parse_args(int argc, char **argv, t_ls *ls);
void list_dir(char *path, t_opts *opts, t_ls *ls);

// utils
int ft_strcmp(const char *s1, const char *s2);
char    *ft_joinpath(char *path, char *name);
char	*ft_strjoin(char const *s1, char const *s2);
int cmp_alpha(char *a, char *b);
int cmp_time(char *a, char *b, char *path);
// print
void print_files(char **entries, t_ls *ls, char *path);


#endif