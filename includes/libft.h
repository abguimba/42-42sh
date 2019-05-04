/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 01:51:43 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 09:09:59 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define GARBAGE	0
# define PROGRAM	"42sh"

void				*ft_memset(void *b, int c, size_t len);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

void				ft_bzero(void *s, size_t n);

size_t				ft_strlen(const char *s);

char				*ft_strdup(const char *s1);

char				*ft_strndup(const char *s1, int nb);

char				*ft_strcpy(char *dst, const char *src);

char				*ft_strncpy(char *dst, const char *src, size_t len);

char				*ft_strcat(char *s1, const char *s2);

char				*ft_strncat(char *s1, const char *s2, size_t n);

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_strncmplc(const char *s1, const char *s2, size_t n);

int					ft_isalpha(int c);

int					ft_atoi(const char *str);

int					ft_isdigit(int c);

int					ft_isascii(int c);

int					ft_isspecial(int c);

int					ft_isprint(int c);

int					ft_toupper(int c);

int					ft_tolower(int c);

char				*ft_strstr(const char *haystack, const char *needle);

char				*ft_strnstr(const char *hs, const char *nl, size_t len);

char				*ft_strchr(const char *s, int c);

char				*ft_strrchr(const char *s, int c);

size_t				ft_strlcat(char *s1, const char *s2, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memchr(const void *s, int c, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

int					ft_isalnum(int c);

void				*ft_memalloc(size_t size);

void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);

void				ft_strdel(char **as);

void				ft_strclr(char *s);

void				ft_striter(char *s, void (*f)(char *));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmap(char const *s, char (*f)(char));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);

int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, size_t t, size_t l, size_t f);

char				*ft_strjoinfree(char *s1, char *s2, size_t freelv);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strrev(char const *s1, int freeit);

char				*ft_strtrim(char const *s);

void				ft_putchar(char c);

void				ft_putstr(char const *s);

void				ft_putstr_nocar(char const *s);

char				**ft_strsplit(char const *s, char c);

size_t				ft_countchars(char const *s, char c);

char				*ft_itoa(int n);

void				ft_putnbr(int n);

void				ft_putendl(char const *s);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char const *s, int fd);

void				ft_putendl_fd(char const *s, int fd);

void				ft_putnbr_fd(int n, int fd);

char				*ft_strsubuntilchar(char const *s, size_t start, char end);

int					get_next_line(int const fd, char **line);

int					ft_tablen(char **tab);

void				free_tab(char **tab);

char				**ft_split_white(char *str);

char				*ft_strjoinchar(char const *s1, char s2, size_t free_level);

long				ft_atoi_check(char *nptr);

int					ft_isinteg(char *str);

typedef struct		s_list
{
	void			*content;
	size_t			index;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content);

t_list				*ft_lstgetfirst(t_list *lst);

t_list				*ft_lstgetlast(t_list *lst);

t_list				*ft_lstadd(t_list *listelement, t_list *newelement);

void				ft_lstdelone(t_list *elementlist, int free_content);

void				ft_lstdel(t_list *lst, int free_content);

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list				*ft_lstget(size_t index, t_list *anyelement);

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void				ft_lstswap(t_list *anyelement, int index1, int index2);

typedef struct		s_lstcontainer
{
	void			(*add)(struct s_lstcontainer *lstc, void *cont);
	void			(*remove)(struct s_lstcontainer *lstc, t_list *el, int f);
	int				(*size)(struct s_lstcontainer *list_container);
	int				(*fastsize)(struct s_lstcontainer *list_container);
	void			(*reindex)(struct s_lstcontainer *list_container);
	t_list			*firstelement;
	t_list			*lastelement;
}					t_lstcontainer;

typedef struct		s_lone_ptr
{
	void				*ptr;
	struct s_lone_ptr	*next;
	struct s_lone_ptr	*prev;
}					t_lone_ptr;

typedef struct		s_ptr_list
{
	struct s_lone_ptr	*first;
	struct s_lone_ptr	*last;
}					t_ptr_list;

void				lstcontainer_add(t_lstcontainer *cont, void *c);

void				lstcontainer_addall(t_lstcontainer *d, t_lstcontainer *c);

void				lstcontainer_remove(t_lstcontainer *l, t_list *el, int f);

int					lstcontainer_size(t_lstcontainer *list_container);

int					lstcontainer_fastsize(t_lstcontainer *container);

void				lstcontainer_reindex(t_lstcontainer *container);

t_lstcontainer		*lstcontainer_new(void);

t_lstcontainer		*ft_strsplitlst(char *str, char c);

void				ft_freesplitlist(t_lstcontainer *list);

void				*ft_malloc(size_t size);

int					ft_free(void *ptr);

int					ft_free(void *ptr);

int					garbage_init(void);

int					mmalloc_init(void);

void				free_all_list(void);

char				**ft_split_whitespaces(char *str);

char				*ft_strdup_nocar(const char *s);

void				free_two_tabs(char **tab1, char **tab2);

t_lstcontainer		*ft_split_with_char(char *str);

int					ft_iswhitespace(int c);

#endif
