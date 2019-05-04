/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:05:10 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 00:42:53 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"
# include "token.h"
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
	int					intrak;
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
	int					intra_key;
	int					error;
	struct s_unquoter	*next;
}				t_unquoter;

typedef struct	s_scan_arg
{
	t_expand	*expand;
	t_scan		*scan;
	t_scan		*first_scan;
	t_unquoter	*checker;
	char		*new_arg;
	int			ret;
}				t_scan_arg;

typedef struct	s_dataq
{
	char		*new_value;
	char		*scan;
	t_unquoter	*to_unquot;
	t_unquoter	*first;
	char		next_quote;
}				t_dataq;

char			expand_transformer(char **value, int unq);
t_expand		*new_expand(int len);
void			create_list_expand(t_expand *new_letter, char *line);
int				have_homedir(char *to_transf);
int				check_have_homedir(struct passwd *user_inf, char *tmp_usr);
void			transform(t_expand *expand, char **str);
void			expand_tilde_only(char **str);
char			*get_user_home(char *user);
void			expand_tilde_path(char **str);
void			delete_list_expand(t_expand **letter);
void			delete_letter_expand(t_expand **letter);
char			*get_home_value(void);
char			*get_parm_string(char *str);
void			expand_tilde_user(char **str);
void			expand_tilde_pwd(char **str, t_expand **expand);
t_expand		*expand_keys(t_expand *expand, char **str);
char			check_sign(t_expand *expand);
void			exp_key_less(char **str, t_expand *expand);
char			*get_varname(t_expand *expand);
char			*get_value(t_expand *expand, int i);
void			exp_key_equal(char **str, t_expand *expand);
void			exp_key_inter(char **str, t_expand *expand);
void			exp_key_plus(char **str, t_expand *expand);
void			exp_key_start_hash(char **str, t_expand *expand);
void			exp_key_unique_hash(char **str, t_expand *expand);
void			exp_key_unique_percent(char **str, t_expand *expand);
void			exp_key_double_percent(char **str, t_expand *expand);
void			exp_key_double_hash(char **str, t_expand *expand);
void			exp_key_altern(char **str, t_expand *expand);
void			transform_if_tilde(t_expand **expand, char **str);
char			is_two_points_sign(t_expand *to_run);
char			is_diferent_sign(t_expand *to_run);
char			is_slash_sign(t_expand *to_run);
void			skip_found(char **str, char *value_var, char *to_srch);
void			select_not_found(char **str, char *value_var, char *to_srch);
char			*varname(char *var, t_expand *to_run);
char			*value(char *val, t_expand *start);
void			scan_arg_transformer(t_unquoter **check, char **value);
t_scan			*new_scan(void);
void			scan_argument(char *arg, t_scan *info_arg);
char			*ft_exp_complete(char *arg);
t_unquoter		*unquote_value(char **value);
int				ft_iswhitespace(int c);
void			print_exp_error(char *to_error, char **str);
void			print_exp_error_eq(char *varname, char *value, char **str);
void			print_exp_str_error(char *strerror, char **str);
void			print_exp_error_inter(char *varname, char *value, char **str);
void			print_exp_token_error(void);
void			print_exp_scan_error(char *strerror);
void			print_exp_invalid(char *error);
int				scan_tilde(char *arg, char **new_arg);
int				scan_dollar(char *arg, char **new_arg);
int				scan_dollar_key(char *arg, char **new_arg);
int				scan_other(char *arg, char **new_arg);
int				transform_simple(char **str);
void			init_analyzer(t_analyzer *to_analy, char **str,
					t_expand *expand);
void			clean_nlzr_wildcard(t_analyzer *to_analy, int reverse);
void			str_uniq_percent_chgr(t_analyzer *to_analy, char **str);
void			print_exp_error_dpoints(char *varname, char *value, int sign,
					char **str);
void			asign_vrvlufnd(t_analyzer *nly, char **rvrvlu,
					char **rwlcd, char **str);
void			asgnvrvluastrk(t_analyzer *nly, char **rvrvlu,
					char **rwlcd, char **str);
void			rmv_str(char **str);
void			ass_str_wout_ast(t_analyzer *to_analy, char **str);
void			ass_str_wstrt_ast(t_analyzer *to_analy, char **str);
void			ass_str_wend_ast(t_analyzer *to_analy, char **str);
void			expan_arg(t_scan_arg *scarg);
void			fill_scarg(t_scan_arg *scarg);
t_unquoter		*new_unquoted_value(void);
void			copy_to_quote(char **old, char **new, char *type);
void			copy_new_value(char **old, t_unquoter **new);
t_unquoter		*quote_checker(t_unquoter *to_unquot, char **ascan);
void			clean_unquoter(t_unquoter *unq);
void			end_analyzer(t_analyzer to_analy);
void			scan_lstdel(t_scan *scan);
void			expand_lstdel(t_expand *expan_head);
void			reassign_str_altern(char **str, t_analyzer *to_analy);
void			update_envp(void);
t_last			*check_exp_error(t_last *cmd);
void			ft_add_setenv_string(char *s1, char *s2);
int				is_sym(char *str);
void			run_to_first_invalid(t_last **cur);
void			rmv_cur_cmd(t_last **cur_cmd);
t_last			*skip_valid_cmd_obj(t_last *cmd);
t_last			*cut_cmd(t_last *cmd, t_last *begin, t_last *prev,
					t_last *next);
void			re_format_line(t_last **first);
t_last			*chg_env_and_set_vars(t_last *cmd);
t_last			*check_for_local_vars(t_last *list_cmd);
int				is_invalid_char(t_expand *to_run);
t_last			*run_to_next_cmd(t_last *cmd, t_last *next);
int				is_bad_expansion(char *to_eval);
int				check_expand_tab(char **tab_to_eval);
int				check_expand_tab_builtin();
void			quotenize(t_unquoter *first, char **value);
t_unquoter		*re_create_intra_keys(t_unquoter *to_unquot, char **tmp);
int				heredoc_expander(char **str);
t_unquoter		*unquoter_prepare(t_unquoter *to_unquot);
char			*back_slash_error(char *str);
int				assign_to_curpid(char **str);
int				assign_to_lastreturn(char **str);
int				assign_to_shell_name(char **str);
int				assign_to_lastbackground(char **str);
int				assign_to_lastargument(char **str);
void			clean_value(char **value, int unq);

#endif
