/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:06:23 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 01:14:19 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "sh42.h"

typedef struct	s_fcparse
{
	int					e;
	int					l;
	int					r;
	int					n;
	int					s;
	int					i;
	int					err;
	int					low;
	int					max;
	char				*str;
	char				*editor;
	char				*first;
	char				*last;
	char				*shist;
}				t_fcparse;

void			free_and_null(void *ptr);
int				k_main(void);
int				ft_exit3(int exitcode, int mode);
int				exit_errors(int error);
int				show_setenv(void);
void			replace_env_set_str(char *varname, char *varvalue);
int				check_and_exec_echo(void);
int				is_builtin_alone(int singleq, int doubleq);
int				ft_builtin_search(char *builtin);
int				is_builtin(void);
int				ft_exit2(int exitcode);
int				unsetenv_errors(int mode);
int				builtin_exec();
int				setenv_errors(int mode);
int				ft_unsetenv(void);
int				ft_setenv(void);
int				jobs_builtin(void);
int				errors_fg(int nb, int error, char *hold);
int				errors_bg(int nb, int error, char *hold);
int				ft_cd(int i);
int				getright(char *str, char *err);
int				bg_builtin(void);
int				fg_builtin(void);
int				ft_unset(void);
int				ft_export(void);
int				export_error(char *error);
void			assign_to_env_save_value(char *varname, char *varvalue,
					char *arg);
void			assign_to_env_replace_value(char *varname, char *varvalue,
					char *arg);
void			assign_to_env_if_not_exist(char *varname, char *varvalue,
					char *arg);
int				ft_env(void);
char			*clean_env_i(char *str, int jsave);
int				builtin_exec_cont_2(void);
int				test_exist_dir(char *path);
char			*add_pwd(char *path, char option);
char			*add_slash(char *pathname);
char			*sanitize_path_cd(char *path, char option);
char			*cd_path(char *path);
int				ft_changedir(char *path, char option, char *err, int i);
int				history_builtin(void);
void			alias_loop_zero(void);
int				alias_print_error(char *alias);
int				alias_add_error(char *alias);
int				search_eq(char *alias);
int				fc_builtin(void);
t_fcparse		*fc_option(char **av, int i);
t_fcparse		*fc_offset(char **av, t_fcparse *opt);
int				fc_error(int i, char *str);
void			char_to_index(t_fcparse *opt);
void			print_fc(t_fcparse *opt);
int				create_fc_file(t_fcparse *opt);
void			get_neg_offset(t_fcparse *opt);
void			fc_loop(char *path);
t_list			*clean_jobs_next_tmp(char *line, t_list *tmp);
void			fc_edit(t_fcparse *opt, char *path);
int				eq_sign(char *str);
int				create_fc_oldnew(t_fcparse *opt);
char			*rebuild_line(t_lstcontainer *list);
int				fc_mode(t_fcparse *opt);
char			*unquote(char *eof);
void			swap_list(t_lstcontainer *list, t_fcparse *opt);
int				set_kirby_screen(void);
int				read_samurai(void);
int				print_win(int i);
int				print_box(int i);
int				print_file(int i);
int				rand_loop(int a, int b);
void			print_stylish(int i);
int				duel(int i);
int				too_soon(char buf);
char			*get_file(int i);
char			*get_box_file(int i);
int				special_main(void);
int				check_two_arg(char **argv);
int				check_three_arg(char **argv);
int				game_loop(void);
int				print_usage(void);
int				error_file(char *file);
void			hist_set_unset(int i, t_fcparse *opt);

#endif
