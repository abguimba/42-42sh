/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:05:10 by mjose             #+#    #+#             */
/*   Updated: 2019/03/21 02:05:58 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"
# include "minishell.h"
# include <pwd.h>
# include <uuid/uuid.h>

typedef struct	s_expand
{
	char				ltr;
	int					len;
	int					idx;
	struct s_expand		*next;
	struct s_expand		*prev;
}				t_expand;

typedef struct	s_env_set
{
	struct s_keyval		*param;
	struct s_env_set	*next;
}				t_env_set;

typedef struct	s_scan
{
	char				*sstring;
	int					error;
	struct s_scan		*next;
}				t_scan;

typedef struct	s_analyzer
{
	char		*orig_str;
	int			orig_len;
	char		*varname;
	int			vnme_len;
	char		*varvalue;
	int			vvlu_len;
	char		*wildcard;
	int			wlcd_len;
	int			asterisk;
	int			start_astrsk;
	int			end_astrsk;
}				t_analyzer;

typedef struct	s_unquoter
{
	char				*str_unquoted;
	char				type;
	int					error;
	struct s_unquoter	*next;
}				t_unquoter;

char			expand_transformer(char **value, int chg_value);
int				need_expand(char *to_transf);
t_expand		*new_expand(int len);
void			create_list_expand(t_expand *new_letter, char *line);
int				have_homedir(char *to_transf);
int				check_have_homedir(struct passwd *user_inf, char *tmp_usr);
int				have_parm(char *to_transf);
int				is_to_add_or_mod_parm(char *to_transf);
int				transform(t_expand *expand, char **str);
void			expand_tilde_only(char **str);
char			*get_user_home(char *user);
void			expand_tilde_path(char **str, t_expand **expand);
int				is_path_tilde(char *to_transf);
void			delete_list_expand(t_expand **letter);
void			delete_letter_expand(t_expand **letter);
void			update_list_expand(t_expand **letter, char **str);
char			*get_home_value(void);
char			*get_parm_string(char *str);
void			expand_tilde_user(char **str, t_expand **expand);
void			expand_tilde_pwd(char **str, t_expand **expand);
t_expand		*expand_keys(t_expand *expand, char **str);
char			check_sign(t_expand *expand);
void			exp_key_less(char **str, t_expand *expand);
char			*get_varname(t_expand *expand);
char			*get_value(t_expand *expand);
void			exp_key_equal(char **str, t_expand *expand);
void			exp_key_inter(char **str, t_expand *expand);
void			exp_key_plus(char **str, t_expand *expand);
void			exp_key_start_hash(char **str, t_expand *expand);
void			exp_key_unique_hash(char **str, t_expand *expand);
char			*get_asterisk_value(t_expand *expand);
void			exp_key_unique_percent(char **str, t_expand *expand);
char			*get_value_asterisk(t_expand *expand);
void			exp_key_double_percent(char **str, t_expand *expand);
void			exp_key_double_hash(char **str, t_expand *expand);
void			exp_key_altern(char **str, t_expand *expand);
void			transform_if_tilde(t_expand **expand, char **str);
char			is_two_points_sign(t_expand *to_run);
char			is_diferent_sign(t_expand *to_run);
char			is_slash_sign(t_expand *to_run);
void			skip_found(char **str, char *value_var, char *to_srch);
void			select_not_found(char **str, char *value_var, char *to_srch);
void			select_last_not_found(char **str, char *value_var,
					char *to_srch, char *found);
char			*varname(char *var, t_expand *to_run);
char			*value(char *val, t_expand *start);
char			*value_asterisk(char *val, t_expand *start);
int				have_envname(char *var);
int				have_setname(char *var);
void			scan_arg_transformer(t_unquoter **check, char **value);
t_scan			*new_scan(void);
void			scan_argument(char *arg, t_scan *info_arg, int simple,
					char quote);
char			*ft_exp_complete(char *arg);
t_unquoter		*unquote_value(char **value);
void			reassign_value(char **value, char *new_value, int quote);
int				quote_error(char *scan, int open_key, int quote);
void			unquote(char **value, int *quote);
int				ft_iswhitespace(int c);
void			print_exp_error(char *to_error);
void			print_exp_error_eq(char *varname, char *value);
void			print_exp_str_error(char *strerror);
void			rmv_tab_exec(char **tab_exec, int to);
int				is_simple_expand(char *value);
void			scan_simple_arg_transformer(char **arg);
int				scan_tilde(char *arg, char **new_arg);
int				scan_dollar(char *arg, char **new_arg);
int				scan_dollar_key(char *arg, char **new_arg);
int				scan_other(char *arg, char **new_arg);
int				transform_simple(char **str);
void			init_analyzer(t_analyzer *to_analy, char **str,
					t_expand *expand);
void			clean_nlzr_wildcard(t_analyzer *to_analy, int reverse);
void			str_uniq_percent_chgr(t_analyzer *to_analy, char **str);
void			print_exp_error_dpoints(char *varname, char *value, int sign);
void			asign_vrvlufnd(t_analyzer *nly, char **rvrvlu,
					char **rwlcd, char **str);
void			asgnvrvluastrk(t_analyzer *nly, char **rvrvlu,
					char **rwlcd, char **str);
void			rmv_str(char **str);
void			ass_str_wout_ast(t_analyzer *to_analy, char **str);
void			ass_str_wstrt_ast(t_analyzer *to_analy, char **str);
void			ass_str_wend_ast(t_analyzer *to_analy, char **str);

#endif
