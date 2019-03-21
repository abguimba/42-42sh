/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:06:23 by mjose             #+#    #+#             */
/*   Updated: 2019/03/20 05:12:54 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "sh42.h"

void			add_to_env_set(char *varname, char *varvalue);
t_env_set		*new_envset(char *varname, char *varvalue);
int				show_setenv(void);
void			replace_env_set_str(char *varname, char *varvalue);
int				cd_builtin(void);
int				check_and_exec_echo(void);
int				is_builtin_alone(void);
int				ft_builtin_search(char *builtin);
int				is_builtin(void);
int				ft_exit(void);
int				builtin_exec();
int				jobs_builtin(void);
int				errors_fg(int nb, int error);
int				bg_builtin(void);
int				fg_builtin(void);
int				errors_bg(int nb, int error);
int		        ft_cd(void);
int		        ft_isdir(char *path);
int		        ft_handlestat(struct stat *tmp, char *permission, char *path);
char	        *ft_homepath(char *path);
char	        *ft_cdpath(char *path);
char	        *cd_line(char **tab, char *cdline, char *path);
char	        *conc_and_free(char *path, char **tab);
char		    *ft_dot(char *path);
int		        getright(char *str);

#endif