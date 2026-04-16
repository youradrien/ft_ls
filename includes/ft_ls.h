
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
    char    **files;
    char    **dirs;
    t_opts  options;
} t_ls;

// parse
int parse_args(int argc, char **argv, t_ls *ls);

// utils
int	ft_strcmp(const char *s1, const char *s2);

// print
void print_dirs(t_ls *ls);
void print_dir_content(char *path);
void print_files(t_ls *ls);


#endif