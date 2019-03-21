# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 18:27:43 by cababou           #+#    #+#              #
#    Updated: 2019/03/10 19:01:25 by bsiche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =		ft_atoi.c \
	 ft_bzero.c \
	ft_isalnum.c \
	ft_strndup.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_strjoin.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strsplit.c \
	ft_strstr.c \
	ft_strsub.c \
	ft_strtrim.c \
	ft_strjoinfree.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_strrev.c \
	ft_lstgetfirst.c \
	ft_lstgetlast.c \
	ft_lstdel.c \
	ft_lstget.c \
	ft_strsubuntilchar.c \
	ft_lstswap.c \
	listcontainer_new.c \
	listcontainer_addelement.c \
	listcontainer_addall.c \
	listcontainer_removeelement.c \
	listcontainer_reindex.c \
	listcontainer_size.c \
	ft_strsplitlst.c \
	ft_tablen.c	\
	ft_split_whitespace.c \
	get_next_line.c \
	listcontainer_fastsize.c

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

OBJ := 	$(SRC:.c=.o)

PWD :=		$(shell pwd)

OBJDIR := 	obj

OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

FLAG := -g -Wall -Wextra -Werror

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell ls $(PWD)/obj/ 2> /dev/null | wc -l | sed -e 's/ //g')

all : $(NAME)

$(NAME) : $(OBJP)
			@echo -e "$(CLEAR_LINE)$(COL_RED)lib compilation$(COL_END)"
			@echo -e "$(CLEAR_LINE)$(COL_GREEN)Done ✓$(COL_END)"
			@ar rc $(NAME) $(OBJP)

$(OBJDIR)/%.o: %.c
			@mkdir -p $(ONLYDIR)
			@gcc -g -c -Wall -Wextra -Werror $< -o $@
			@echo "$(CLEAR_LINE)$(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

clean :
			@rm -rf $(OBJDIR)

fclean :	clean
			@rm -rf $(NAME)

re :		fclean all
