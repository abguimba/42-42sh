/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:30:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/08 05:05:31 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <errno.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>

typedef	struct	s_ls
{
	mode_t	permission;
	char	*name;
	off_t	size;
	time_t	time;
	char	*path;
	nlink_t	hardlink;
	uid_t	usrname;
	gid_t	group;
	int		timeswitch;
	long	block;
	size_t	maj;
	size_t	min;
	int		issimple;
	char	acl;
	char	*symlink;
	char	*strusrname;
	char	*strgroup;
	char	*strlink;
	char	*strtime;
	char	*strpermission;
	char	*strsize;
	char	*strmin;
	char	*strmaj;
	char	*strpad;
	int		id;
	int		color;
}				t_ls;

int				ft_option(char **argv, char **str, int *flag);
int				checkoption(char *option, char c);
t_lstcontainer	*ft_ls(char *dossier, char *option, int called);
t_lstcontainer	*makelist(t_lstcontainer *mainliste,
				DIR *dir, char *str, char *option);
t_lstcontainer	*ft_dirliste(t_lstcontainer *dirlist, t_list *mainliste);
t_lstcontainer	*simpleinfo(char *str, char *option);
DIR				*chkdir(char *str, int *check);
int				ft_cleanpath(char *str);
void			makepath(char **path, char *str, char *name);
int				ft_recursive(t_list *liste, char *option);
char			*ft_usrmode(mode_t mode);
int				ft_stat(char *path, t_ls *info, char *option);
char			*ft_getusr(uid_t pw);
char			*ft_getgroup(gid_t gr);
int				ft_print(t_list *liste, char *option, int flag);
int				ft_printl(t_list *liste, int g);
int				ft_strinfo(t_list *liste);
void			ft_cleantime(t_list *liste);
void			ft_spacegroup(t_list *liste);
void			ft_spacesize(t_list *liste);
void			ft_spacelink(t_list *liste);
int				ft_getmaxlen(t_list *liste, int i, size_t maxsize);
void			ft_cleanid(t_list *liste);
size_t			ft_getidlen(t_list *liste, int i);
void			ft_spaceusr(t_list *liste);
t_list			*ft_mergesort(t_list *liste, int i);
t_list			*cmptime(t_list *start, t_list *mid);
t_list			*cmptimename(t_list *start, t_list *mid);
void			ft_sort(t_list *liste, char *option);
void			ft_total(t_list *liste);
int				ft_strpad(t_list *liste, int g);
int				getsize(int max);
int				needstat(char *str);
void			color(t_list *liste);
void			ft_putcolor(int i);
void			ft_usage(char invalid);
void			ft_freestruct(t_list *liste);
t_ls			*str_alloc();
char			*ft_subtime(char *dup, char *tmp);
char			*getblank(size_t j, size_t k);
int				getspacesize(t_list *liste);
t_lstcontainer	*free_all(t_lstcontainer *mainliste, char *dossier);
void			ft_freestructlite(t_ls *tmp);
void			reverselist(t_list *liste);
char			*clean1(char *option, int i, int j);
char			*truename(char *str);
void			reindex(t_list *liste);
int				ft_edgecase(char *dossier);
char			*truename2(char *str);
void			get_and_sort(t_lstcontainer *mainliste, char *option);
int				get_coltab(t_list *liste, int g);
#endif
