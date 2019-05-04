/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 06:02:09 by abguimba          #+#    #+#             */
/*   Updated: 2019/05/04 07:22:53 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# include "libft.h"
# include "ft_ls.h"
# include "token.h"
# include "expansions.h"
# include "tmp_local_env.h"
# include "builtins.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <fcntl.h>

# define ANSI_COLOR_BLUE	"\x1b[36m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_DEFAULT "\x1b[0m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_RED		"\x1b[31m"

# define SHELL_NAME			"42sh"
# define K_FN1				"\x1b\x4f\x50"
# define K_FN2				"\x1b\x4f\x51"
# define K_FN3				"\x1b\x4f\x52"
# define K_LEFT				"\x1b\x5b\x44"
# define K_RIGHT			"\x1b\x5b\x43"
# define K_DOWN				"\x1b\x5b\x42"
# define K_UP				"\x1b\x5b\x41"
# define K_END				"\x1b\x5b\x46"
# define K_HOME				"\x1b\x5b\x48"
# define K_LUP				"\x1b\x5b\x31\x3b\x32\x41"
# define K_LDOWN			"\x1b\x5b\x31\x3b\x32\x42"
# define K_WLEFT			"\x1b\x5b\x31\x3b\x32\x44"
# define K_WRIGHT			"\x1b\x5b\x31\x3b\x32\x43"
# define K_RTN				10
# define K_RT				13
# define K_SPC				32
# define K_BKSP				127
# define K_TAB				9
# define K_CTRLR			18
# define K_ESC				"\x1b\x1b"
# define K_DEL				"\x1b\x5b\x33\x7e"

typedef struct	s_cursor
{
	int					prompt;
	int					abs;
	int					x;
	int					y;
	int					relabs;
	int					relx;
	int					rely;
	int					legacy;
}				t_cursor;

typedef struct	s_term_data
{
	int					sizex;
	int					sizey;
}				t_term_data;

typedef struct	s_auto
{
	char				*word;
	char				*path;
	char				*menuline;
	t_lstcontainer		*bin_lst;
	t_lstcontainer		*var_lst;
	t_lstcontainer		*comp_list;
	t_lstcontainer		*to_free;
	t_lstcontainer		*page_lst;
	int					active_page;
	int					per_page;
	int					page_nbr;
	int					type;
	char				*to_add;
	int					col_nbr;
	int					lin_nbr;
	int					size;
	int					line_up;
	int					last_page;
	int					pad_lpage;
	int					hidden;
	int					err;
	int					to_add_y;
	int					to_rem;
}				t_auto;

typedef struct	s_cpaste
{
	int					b1;
	int					b2;
	char				*line;
}				t_cpaste;

typedef struct	s_keyval
{
	char				*key;
	char				*value;
	int					loop;
}				t_keyval;

typedef struct	s_tree
{
	int					type;
	char				*cmd;
	t_last				*list_cmd;
	struct s_tree		*right;
	struct s_tree		*left;
	struct s_tree		*prev;
}				t_tree;

typedef struct	s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}				t_env;

typedef struct	s_shell
{
	t_lstcontainer	*alias_lst;
	t_lstcontainer	*env;
	t_lstcontainer	*set_env;
	t_lstcontainer	*hist;
	t_env			*tmpenvsave;
	t_env			*setsave;
	char			**tab_env;
	char			**tab_reddir;
	int				err_expend;
	int				err_expend_printed;
	int				in_ast;
	int				in_here;
	int				is_expanded;
	int				errchk;
	int				dup1;
	int				dup2;
	int				dup3;
}				t_shell;

typedef struct	s_hash
{
	char				*binary;
	char				*path;
	int					totalhits;
	struct s_hash		*nextbinary;
}				t_hash;

typedef struct	s_alias
{
	int					alias_len;
	int					next_alias;
	char				*alias;
	struct s_alias		*next;
}				t_alias;

typedef struct	s_tracking
{
	struct termios		default_term;
	struct termios		myterm;
	struct s_term_data	*terminfo;
	struct s_cpaste		*cpaste;
	struct s_auto		*aut;
	struct s_shell		*mysh;
	struct s_jobs		*jobs;
	struct s_hash		*hashtable[27];
	struct s_ptr_list	*garbage;
	struct s_ptr_list	*mmalloc;
	struct s_alias		*aliasloop;
	char				**g_tab_exec;
	char				*tmp_hist;
	int					builtin;
	t_cursor			*pos;
	t_last				*temp_command;
	char				*str;
	char				*cmd;
	char				*user;
	char				*cwd;
	char				*prompt;
	char				*search;
	char				*found;
	t_lstcontainer		*key_list;
	t_lstcontainer		*builtin_list;
	int					linemode;
	int					quotes;
	int					bracket;
	int					swi;
	int					buffsize;
	int					histindex;
	int					histmax;
	int					interactive;
	int					lastreturn;
	int					expandreturn;
	int					lastbackground;
	int					sterminal;
	pid_t				spid;
	int					shebang;
	int					herenbr;
	int					herexpnd;
	int					foreground;
	int					hist_first;
	int					fc;
}				t_tracking;

typedef struct	s_comm
{
	int					status;
	struct s_comm		*next;
	pid_t				cpid;
	int					done;
	int					stopped;
}				t_comm;

typedef struct	s_jobs
{
	int					currentback;
	int					current;
	int					startback;
	struct s_jobs		*next;
	struct s_jobs		*prev;
	char				*name;
	char				wd[4096 + 1];
	int					stdin;
	int					stdout;
	int					stderr;
	int					place;
	int					foreground;
	int					background;
	pid_t				jpid;
	int					notified;
	int					backstart;
	struct termios		jterm;
	struct s_comm		*t_command;
}				t_jobs;

t_tracking		g_tracking;

void			init_shell(char **environ);
char			*ft_usrmode(mode_t mode);
char			*ft_true_pwd(void);
int				get_key(void);
int				check(char *str);
int				single_key(char c);
int				return_loop(int i, char *str);
int				readloop(int i, int fd, char *str);
int				basic_mode(void);
void			ft_return(void);
int				ft_exec_key(char *str);
int				is_cmd(char *str);
int				yan_putchar(int c);
void			get_term(void);
int				clear_screen3(void);
void			update_pos(void);
void			add_to_str(char *str);
void			rem_from_str(void);
void			rem_from_str_del(void);
void			get_size(void);
int				utf_strlen(char *str);
int				get_nb_char(unsigned char c);
int				utf_goto(char *str, int j);
void			go_home(void);
void			go_end(void);
void			print_line(void);
void			back_to_pos(void);
void			move_to_end(void);
void			move_left(void);
void			move_right(void);
void			back_home(void);
void			cursorinit(void);
void			cursor_reset(void);
void			move_up(void);
int				check_up(void);
void			move_down(void);
int				check_down(void);
void			next_word(void);
void			prev_word(void);
void			print_and_go(int i);
int				rev_utf_goto(char *str, int j);
void			begin_cpy(void);
void			begin_paste(void);
void			print_line_cpy(int start, int end);
t_lstcontainer	*modified_ls(int argc, char **argv);
int				auto_complete(void);
void			check_hidden(void);
int				check_type(void);
void			get_max_size(void);
void			ft_strpadding(void);
t_lstcontainer	*build_ls(void);
void			build_comp(t_lstcontainer *list);
void			completion_loop(t_lstcontainer *list);
void			complete_usr_word(void);
void			complete_usr_var(void);
int				is_space_ac(char *tmp, int i);
void			rem_str(char *str);
void			assign_type(void);
void			clean_up_autoc(void);
int				ft_menuline(void);
void			back_up_add(void);
void			go_back_down(void);
char			*send_color(int i);
void			color(t_list *liste);
int				is_spaces(char *str, int i, int mode);
int				print_menu(void);
int				end_autocomplete(int i);
int				end_word(int mode);
void			cmd_lstdel(t_last *cmd);
t_last			*new_list(void);
void			build_bin_lst(void);
t_list			*move_arround(t_list *buf, int i);
void			set_up_page(void);
t_lstcontainer	*build_page_lst(t_lstcontainer *list);
void			build_var_lst(void);
void			change_page(int i, t_lstcontainer *list);
void			join_page_nbr(void);
void			line_per_page(void);
void			escape_path(void);
int				alias_or_orig(char *orig, char *value, int i, char *content);
void			add_used_alias(char *alias);
int				clean_used_alias(int returncode);
int				check_if_used_alias(char *str, int i, int j);
int				inf_loop(char *origkey, char *aliasval, int i, t_list *hold);
char			*swap_alias(char *str, int j, int isave, t_keyval *tmp);
void			swap_alias_helper(char *n, int l, int i, char *str);
int				get_last_char_alias(char *str, char *memory, int nbsave, int j);
char			*check_if_next_alias(char *str);
char			*next_alias_recursive(char *str);
char			*check_if_first_word_alias(char *str, int i, int isave);
int				next_separator(char *str, int i);
char			*swap_alias(char *str, int j, int isave, t_keyval *tmp);
char			*aliased_line(char **taab, int i, int loop, char *hold);
char			*alias_swapper(char *line, int i, int count);
char			**line_to_taab(char *str, int i, int j);
void			set_alias_globals(char *value, int i, int j);
void			alias_swapper_helper(int i, int j, char *line, char **taab);
char			*taab_to_line(char **taab, char *hold);
int				init_alias(int fd, t_lstcontainer *alias_lst);
void			init_new_tmp_env(t_env *tmp, char *str);
int				verify_path_is_valid(char *path);
char			*recursive_alias(char *str);
int				add_alias(int count, char **av);
t_keyval		*parse_alias(char *alias);
int				check_alias_exists(t_keyval *tmp);
char			*return_alias(char *name);
int				print_alias_lst(void);
int				unalias(char *alias);
int				unalias_blt(void);
int				two_arg(char **argv, int i);
char			**copy_tab_minus_one(int argc, char **argv);
int				count_arg(char **taab);
int				three_arg(char **argv);
t_lstcontainer	*type_ls(int argc, char **argv);
char			*get_env_string(char *str);
t_lstcontainer	*ft_env_to_lst(char **environ);
int				replace_env_str(char *s1, char *s2);
void			ft_add_env_string(char *s1, char *s2);
char			*remove_env_string(char *str);
char			*ft_true_pwd(void);
void			add_missing_string(void);
void			ctrl_d(void);
void			ctrl_c(void);
void			clean_up_leaks(void);
t_ls			*ls_alloc(char *str);
int				ctrl_key(char c);
void			is_still_atty(void);
void			jobs_builtin_output(t_jobs *tmp, int mode, int number,
					int options);
int				bg_builtin_output(t_jobs *tmp, char *hold);
int				fg_builtin_output(t_jobs *tmp, char *hold);
int				type_main(void);
char			*exist_fonction(char *cmd);
char			*quote_check(char *str);
char			*ft_modif_line(char *line);
int				check_basic_quotes(char *line);
char			**convert_backtab(char **taab);
int				is_escape(char *str, int i);
void			hist_file_to_lst(char *path, char *line, int fd);
void			hist_save_file(void);
void			print_history(void);
char			*create_path_hist(void);
void			free_hist(void);
int				get_last(void);
int				go_to(int i);
int				history_up(void);
int				history_down(void);
t_last			*create_new_list(void);
void			convert_list(t_last *list);
t_last			*ft_parseur(int i, char *str, t_last *list_cmd, t_last *templ);
void			ft_lexeur(t_last *list_cmd);
void			ft_ast(t_last *list_command);
void			execute_ast(t_tree *tree, t_jobs *job);
int				exec_command(t_last *list, int foreg, t_jobs *job, int readp);
void			convert_list(t_last *list);
int				its_reddir(t_last *list);
int				its_fd_reddir(t_last *list);
int				its_pipe(t_last *list);
int				its_separator(t_last *list);
char			*its_quote(int i, char *str, int *nb, char c);
char			**create_tab_to_exec(t_last *list);
int				execute_pipe(t_last **list, t_jobs *job, int readpipe,
					char ***tab_reddir);
void			execute_two(char **tab_cmd, char **tab_exec_hold);
void			execute_three(char **tab_exec, char **tab_exec_hold, char *p);
void			execute_pipe_two(char **tab_exec, t_jobs *job, int readpipe,
					char ***tab_reddir);
void			close_fd(void);
char			**test_exist_fonct(char **t_c, int mode, char *p, char **pl);
int				error_lexer(t_last *list_cmd);
int				create_fich(char **tab_reddir, int i);
int				its_eper(t_last *list);
char			**tab_dup(char **tob);
char			*search_fd_reddir(char *str);
char			*search_reddir(char *str);
char			*search_normally_arg(char *str, int *nb, int i);
char			*search_symboll(char *str);
int				its_not_symbol(char c);
char			*check_quote(char c);
char			*check_bracket(char *line, int i);
int				ft_valid_quote(char *line, char c, int flag);
int				ft_valid_bracket(char *line);
int				its_heredoc(char *str);
int				its_indir(char *str);
int				out_redir(char **tab_reddir, int i);
void			exec_in_pipe(t_last *list_cmd, t_jobs *job, int descrf[2]);
int				exec_create_file(t_last **list_cmd);
void			set_jobs(t_jobs *job, pid_t pid0);
void			jobs_builtin_mode_helper(t_jobs *tmp, int options);
void			set_new_process(t_jobs *job, pid_t pid0);
void			free_ast(t_tree *tree, t_last *next_free);
t_last			*ret_error(char *line);
int				search_in(char *str, int mode);
int				its_double_reddir(char *str);
int				make_reddir(char **tab_reddir, int i);
void			restore_fd(void);
void			save_fd(void);
void			save_reddir(t_last **list, char ***tab_reddir);
void			execute_reddir(char ***tab_reddir);
int				clean_reddir(char ***tab_reddir);

void			get_coolprompt(void);
void			print_prompt(void);
void			transform_cwd(int i);
int				spaces_line_check(char *line);

void			interactive_check_set_shell_group(void);
void			set_shell_signal_handlers(void);
void			set_process_signal_handlers(void);
t_comm			*new_process(t_jobs *job, pid_t cpid);

void			continue_job(t_jobs *job, int foreground);
void			hash_binary(void);
int				hash_maker(const char c);
t_hash			*new_binary_hash(char *binary, char *path, int hits);
int				errors_hash(char *binary, int error);
int				ft_hash(void);
int				empty_hash_table(void);
char			*hashed_command(char **tab_exec, int index);
int				ft_hash_arg(int j);
void			ft_hash_output_helper(t_hash *tmp, int spaces);
void			hash_update_helper(t_hash *tmp, int index, int j, char **c);
int				hash_update_commands(int j);

int				argc_error(void);
int				exec_errors(char **tab_exec, int mode);
void			free_mysh(void);

void			free_tabs_and_exit(char **envhold, char **tab_exec_hold);
t_jobs			*new_job_helper(t_jobs *tmp);
char			*job_name_maker_helper(int spaces, int len, t_last *head);
t_jobs			*new_job(t_last *part, int background);
void			wait_for_job(t_jobs *job);
void			put_job_in_foreground(t_jobs *job, int cont);
void			put_job_in_background(t_jobs *job, int cont);
int				job_is_done(t_jobs *job);
int				job_is_stopped(t_jobs *job);
char			*parse_job_number(char *str);
int				job_exists(int place);
int				parse_job_sign(char *str);
int				errors_jobs(char option, int nb, int error);
int				suspended_jobs_count(void);
void			free_all_jobs(void);
void			update_status(void);
int				update_process_status(pid_t pid, int status);
void			show_job_info(t_jobs *job, const char *status, int mode, int s);
void			free_job(t_jobs *job);
void			jobs_notifications(void);
void			jobs_update_current(void);
int				update_st_help(t_jobs *job, pid_t pid, t_comm *cmd, int status);
int				job_control_errors(pid_t pid, int mode, int returnvalue);
void			show_job_info_helper(t_jobs *job, int mode);
void			jobs_notifications_output(t_jobs *job);
void			jobs_notif_h(t_jobs *job, t_jobs *last, t_jobs *next, int stat);
void			reset_all(void);
int				main_test(int flag, int i, int argc, char **n);
char			**init_envp(t_lstcontainer *env);
int				exist_builtin(char *cmd);
t_last			*check_exp_error(t_last *cmd);
void			free_keyval(t_lstcontainer *list);
void			next_cmd_update(void);
void			set_expand_return(void);
void			put_unexpected_token(char *sym);
char			*exec_create_heredoc(char *eof);
char			*end_line(char *line);
int				check_eol(char *line);
void			close_fd_copy(void);
char			*alias_and_env(char *line);
void			init_str(void);
void			ft_lstdelcmd(t_last *el);
void			test_loop(char **argv, char *line);
void			main_loop(char *line);
void			assign_word(void);
int				exec_sh(void);
int				exit_reddir(void);
char			*get_hist_ptr(char *needle);
int				begin_search(void);
void			tmp_char_hist(void);
char			*parse_bang(char *line);
char			*get_word(char *word);
char			*get_index(char *word);
char			*replace_word(char *line, int i);
char			*replace_double(char *line, int i);
char			*return_error_bang(void);
void			print_keyval(t_keyval *tmp);
char			*convert_backslash(char *line);
char			get_char_helper(char c);
char			reset_char_helper(char c);
char			*convert_back(char *line);
char			*remove_back(char *line, int i);
int				tab_exec_arg(char ***tab_exec, char ***tab_farg, int i_arg,
					int i);
char			**end_exec_tab(char **tab_exec);
char			*assign_reddir(char *orig);
char			*check_multi_slash(char	*path);
int				is_dir(char *path);

#endif
