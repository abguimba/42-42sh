/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:22:50 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 18:28:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PO line[*i] && line[*i] == '('
# define PF line[*i] && line[*i] == ')'
# define GO line[*i] == '"'
#define CMD 1
#define OPT 2
#define ARG 3
#define FICH 4
#define OP 5
#define SEP 6
#define DESCR 7
#define PATH 8

# include "ft_printf.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct	s_tab
{
	char	**tab_word;
	char	**tab_path;
}				t_tab;

typedef struct	s_env
{
	char	**env;
}				t_env;


typedef struct	s_last
{
	int				check;
	int				type;
	char			*name;
	struct s_last	*next;
	struct s_last	*prev;
}				t_last;


int				ft_strcmp(const char *s1, const char *s2);
int				nb_env(char **env);
int				check_is_env(char *str);
void			forfree(char **tab_free);
int				verif_char(char *line);
void			search_and_affich_env(char *tab_env, char **env);
char			*recup_path(char **env, char *str);
void			modif_pwd(char **env, char *str);
int				get_next_line(const int fd, char **line);
char			**ft_split_whitespaces(char *str);
char			**ft_strsplit(char const *s, char c);
void			set_env(t_env *st_env, char **env);
void			ft_unsetenv(t_env *st_env, t_tab *st_tab);
void			affich_env(t_env *st_env, t_tab *st_tab);
char			*get_pwd(char **env);
void			change_pwd(char ***env, char *pwd);
void			change_last_pwd(char **env, char *pwd);
char			*get_last_pwd(char **env);
void			ft_echo(t_tab *st_tab, t_env *st_env);
void			ft_setenv(t_env *st_env, t_tab *st_tab);
void			realize_built(t_tab *st_tab, t_env *st_env,
		char **line, char **env);
int				check_is_builtins(t_tab *st_tab);
int				existe_env(char **env, char *str);
void			modif_env(char **env, char *str);
char			**duplicate_tab(char ***tab_dup);
char			**duplicate_tab_two(char ***tab_dup, int j);
char			**duplicate_env(char **tab_dup);
void			create_env(char ***env, char *str);
void			delete_env(char ***env, char *str);
void			freetab(char **tab_free);
void			apply_cmd(t_tab *st_tab, t_env *st_env,
		t_last *list_cmd);
int				search_symbol(char *cmd);
void			apply_builtin(t_tab *st_tab, t_env *st_env,
		char *cmd);
t_last			*ft_analize(char *line);

#endif
