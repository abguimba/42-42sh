/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_local_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:30:13 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 01:40:07 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_LOCAL_ENV_H
# define TMP_LOCAL_ENV_H

# include "libft.h"
# include "sh42.h"

int					free_taab_and_return(char **taab, int returncode);
int					next_separator_quotes_check(char *str, int i, int save);
void				argenv_checker(char **arg);
void				restore_env(void);
int					replace_env_str_def(char *s1, char *s2);
void				add_missing_string_def();
char				*check_tmp_env(char *line, int i, int count);
char				*swap_env_cmd_change(char *str, int hold, int i);
void				init_tmp_env(char *key, char *value);
char				*add_tmp_var(char *str, int save, int i);
int					next_separator_env(char *str, int i, int save);
char				*check_first_char_sep(char *line);
char				*tmp_env_namemaker(char *str, int start);
char				*clean_line_tmpenv(char *str, int jsave, int save);
int					free_hold_and_i(int i, char *hold);
void				reset_tmpenv(void);
void				apply_env(void);
void				apply_env_and_del_path(void);
void				check_if_resetenv(void);
int					is_env_alone_check_helper(char *str, int jsave, int isave);
int					skip_tmp_env(char *str, int jsave, int isave);
void				save_tmp_env(char *str, int jsave, int cmdindex);
void				set_tmp_env(char *key, char *value);
char				*check_if_swap_helper(char **taab, int i, char *line);
char				*clean_line_tmp_helper(int len, char *str, int save);
char				*check_if_env_option_i(char **taab, int i, int j, int cmdi);
char				*get_last_env_i(char **taab, int i, int j, int cmdi);
char				*swap_env_var(char *str, int jsave, int cmdindex);
t_lstcontainer		*copyenv(void);
t_last				*remove_tmp_env_list(t_last *begin);
void				reset_resetenv(void);
char				*clean_env_i(char *str, int js);
char				*swap_tmpenv_for_true(char *str, int i);
int					only_spaces_and_sep(char *str);
void				clean_tmp_local_env(void);
char				*get_set_env_string(char *str);
void				free_env(void);
void				look_for_tmpenv(void);
t_last				*tmp_local_vars(t_last *begin, t_last *beginsave);
void				save_local_vars(t_last *begin);
int					its_real_separator(t_last *list);
char				*init_local_env_key(char *str, int i, int j);
t_last				*remove_local_env_list(t_last *begin);
int					check_if_env(char *str, int i);
char				*init_local_env_value(char *str, int i, int j);
int					size_of_key_or_val(char *str, int mode, int count, int i);
void				save_tmp_vars(t_last *begin);

#endif
