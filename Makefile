# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by alsomvil          #+#    #+#              #
#    Updated: 2019/03/21 14:08:23 by hdufer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CLEAR_LINE	= \033[2K
BEGIN_LINE	= \033[A
COL_END		= \033[0m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_VIOLET	= \033[1;35m
COL_CYAN	= \033[1;36m
COL_WHITE	= \033[1;37m

NAME :=	42sh

SRC = main.c \
	  42sh/tools.c \
	  42sh/errors.c \
	  42sh/ft_parseur.c \
	  42sh/ft_lexeur.c \
	  42sh/ft_modif_list.c \
	  42sh/ft_ast.c \
	  42sh/its_token.c \
	  42sh/its_double_token.c \
	  42sh/execute_ast.c \
	  42sh/execute_pipe.c \
	  42sh/add_path_to_bin.c \
	  42sh/create_tab_to_exec.c \
	  42sh/convert_list.c \
	  42sh/create_fich.c \
	  42sh/hashtables.c \
	  42sh/search_arg.c \
	  42sh/completion.c \
	  42sh/check_quote.c \
	  42sh/out_redir.c \
	  42sh/parse.c \
	  42sh/execute_command.c \
	  42sh/exec_create_fich.c \
	  42sh/set_exec_pipe.c \
	  builtins/cd/cd_path.c \
	  builtins/cd/directory.c \
	  builtins/cd/ft_cd.c \
	  builtins/cd/ft_cd2.c \
	  builtins/cd/ft_dotdot.c \
	  builtins/builtin_tools.c \
	  builtins/fg_bg_builtins.c \
	  builtins/jobs_builtin.c \
	  builtins/exit.c \
	  builtins/hash_builtin.c \
	  builtins/builtins.c \
	  builtins/set.c \
	  builtins/echo/exec.c \
	  builtins/type_main.c \
	  builtins/test/test_main.c \
	  builtins/test/test_tab.c \
	  builtins/test/test_two_arg.c \
	  builtins/test/test_three_arg.c \
	  builtins/builtin_errors.c \
	  jobs/signal_handlers.c \
	  jobs/job_utils.c \
	  jobs/job_functions.c \
	  jobs/ft_job_control.c \
	  gnl/coolprompt.c \
	  gnl/add_to_str.c \
	  gnl/rem_from_str.c \
	  gnl/term_setup.c \
	  gnl/init_term.c \
	  gnl/cursor_pos.c \
	  gnl/cursor_check.c \
	  gnl/cursor_arrows.c \
	  gnl/term_size.c \
	  gnl/lib_utf.c \
	  gnl/print_line.c \
	  gnl/next_word.c \
	  gnl/copy.c \
	  gnl/ctrl.c \
	  gnl/paste.c \
	  gnl/get_key.c \
	  gnl/get_cmd.c \
	  gnl/home_end.c \
	  auto_complete/auto_complete.c \
	  auto_complete/auto_complete_check.c \
	  auto_complete/auto_complete_cleanup.c \
	  auto_complete/auto_complete_cursor.c \
	  auto_complete/auto_complete_list.c \
	  auto_complete/auto_complete_page.c \
	  auto_complete/auto_complete_loop.c \
	  auto_complete/auto_complete_move.c \
	  auto_complete/auto_complete_parse.c \
	  auto_complete/auto_complete_padding.c \
	  auto_complete/auto_complete_type.c \
	  auto_complete/print_arg_list.c \
	  auto_complete/send_color.c \
	  auto_complete/var_list.c \
	  auto_complete/end_autocomplete.c \
	  back_search/init_search.c \
	  back_search/search_lst.c \
	  free_func/free_hist.c \
	  ft_ls/cmdparse.c \
	  ft_ls/cmdparse_misc.c \
	  ft_ls/color.c \
	  ft_ls/free_all.c \
	  ft_ls/print.c \
	  ft_ls/ft_clean.c \
	  ft_ls/ft_clean_bis.c \
	  ft_ls/ft_cleanusr.c \
	  ft_ls/ft_devid.c \
	  ft_ls/ft_ls.c \
	  ft_ls/getstat.c \
	  ft_ls/getusr.c \
	  ft_ls/info_to_str.c \
	  ft_ls/main_ls.c \
	  ft_ls/makelist.c \
	  ft_ls/mode.c \
	  ft_ls/mergesort.c \
	  ft_ls/path.c \
	  ft_ls/recursive.c \
	  ft_ls/sortoption.c \
	  ft_ls/termsize.c \
	  ft_ls/timesort.c \
	  alias/alias_bin.c \
	  alias/alias_file.c \
	  alias/alias_struct.c \
	  shell_core/copyenv.c \
	  shell_core/env_to_lst.c \
	  shell_core/init_shell.c \
	  shell_core/get_pwd.c \
	  shell_core/env_list_to_tab.c \
	  history/history_lst.c \
	  history/history_lst2.c \
	  history/history_lst_options.c \
	  history/history_loop.c \
	  history/print_hist.c \
	  history/shebang.c \
	  history/history_lib_plus.c \
	  history/hassantest.c \
	  history/history_builtin_option.c \
	  history/history.c \
	  expansions/expand.c \
	  expansions/user.c \
	  expansions/parm.c \
	  expansions/transform.c \
	  expansions/expand_tilde.c \
	  expansions/tilde.c \
	  expansions/tools_expand.c \
	  expansions/home.c \
	  expansions/expand_keys.c \
	  expansions/check_sign_tools.c \
	  expansions/hash_tools.c \
	  expansions/percent_tools.c \
	  expansions/expand_keys_dblpnt.c \
	  expansions/expand_keys_adv.c \
	  expansions/values.c \
	  expansions/values_tools.c \
	  expansions/environ.c \
	  expansions/environ_set.c \
	  expansions/scan.c \
	  expansions/scan_tilde.c \
  	  expansions/quote.c \
	  expansions/expand_error.c \
	  expansions/analyzer.c \
	  expansions/tools_double_hash.c \
	  expansions/tools_double_percent.c \
	  expansions/autocomplete/auto_com_expan.c

OBJ := $(SRC:.c=.o)

PWD := $(shell pwd)

SRCDIR := srcs
OBJDIR := obj

SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := -L srcs/libft/ -lft

INC := -I includes

FLAG := -g#-Wall -Wextra -Werror 

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(FLAG) $(OBJP) -o $(NAME) -ltermcap $(INC) $(LIB) 
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_BLUE) ᕦ(ò_óˇ)ᕤ$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

libft_comp:
			@make -C srcs/libft

clean :
			@rm -rf $(OBJDIR)
			@make clean -C srcs/libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C srcs/libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"
			
re :		fclean all

.PHONY: ft_printf clean fclean all re