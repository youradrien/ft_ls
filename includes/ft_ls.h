
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
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <time.h>
#include <sys/ioctl.h>

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
void list_dir(char *path, t_opts *opts, t_ls *ls, int i, int first_recursiv__call);

// utils
int ft_strcmp(const char *s1, const char *s2);
char    *ft_joinpath(char *path, char *name);
char	*ft_strjoin(char const *s1, char const *s2);
int     cmp_alpha(char *a, char *b);
int     cmp_time(char *a, char *b, char *path);
int cmp_time_dir(char *dir_1, char *dir_2);
int get_term_width(void);

//symlink
int is_a_symlink(char *path, t_ls *ls);

// print
void print_files(char **entries, t_ls *ls, char *path);
void print_l_total(char **entries, t_ls *ls, char *path);
void print_L(char *path, char *name, int is_linkk);


// tests
/*
- ls [+1pts] 
- ls -a [+1pts] 
- ls -l [+2pts]
- ls -r [+1pts] 
- ls -t [+1pts] 
- ls -r with several files/folders/... as parameter. [+1pts] 
- ls -t with several files/folders/... as parameter. [+1pts] 
- setuid/setgid/stickybit [+1pts]
- ls -R [+2pts]
- ls -larRt ../ ./ src
- ls ('-l -t' for en. as well as '-lt')
- ls zzzz /usr/this_does_not_exist 
- ls -a -a -a -a - a . ../ -R ../
- ls ---a -l
- ls -aaa
- ls -la 
- ls -al 
- ls -ltr
- ls -lrt src includes Makefile
- ls -Ra 
- ls -Rr src src/aa 


// -------------------
// PERMISSION DENIED
mkdir forbidden
chmod 000 forbidden

ls forbidden
ls -l forbidden
ls -R forbidden
// -------------------



// -------------------
// SYMBOLIC LINK
1. Basic symlink
Create:
touch file.txt
ln -s file.txt link

Test:
ls -l link
./ft_ls -l link

Expected format:
lrwxr-xr-x ... link -> file.txt
// -------------------



// -------------------
// UID/GID/STICKYBIT
- setuid
touch test
chmod 4755 test
ls -l test
attendu -> -rwsr-xr-x

- setgid
chmod 2755 test
attendu -> -rwxr-sr-x

- sticky bit
mkdir dir
chmod 1777 dir
attendu -> [drwxrwxrwt]
// -------------------


// -------------------
// ACL/Attribute

ATTRIBUTE
touch testfile
xattr -w test.attr hello testfile
ls -l testfile -> -rw-r--r--@
xattr testfile

ACL
touch aclfile
chmod +a "everyone deny delete" aclfile
ls -l aclfile -> -rw-r--r--+
ls -le aclfile
// -------------------



*/
#endif