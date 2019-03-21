/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 01:45:59 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/05 15:39:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFF_SIZE 60

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

typedef struct	s_save
{
	int		precision;
	int		precisionnull;
	int		largeur;
	int		nbarg;
	int		spaceuni;
	char	conversion;
	char	*start;
	int		space;
	int		pos;
	int		dieze;
	int		zero;
	int		neg;
	int		flagh;
	int		flaghh;
	int		flagl;
	int		flagll;
	int		flagj;
	int		flagz;
	int		retour;
	int		i;
}				t_save;

typedef struct	s_fd
{
	int			fd;
	char		*save;
	char		*free;
	struct s_fd	*next;
}				t_fd;

int				setfd(int fd, int mode);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_printstart(t_save *save, char *tmpformat, int *i);
int				ft_nextarg(va_list test, t_save *save, char *tmpformat, int i);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strsub(char const *s, size_t t, size_t l, size_t f);
void			ft_bzero(void *s, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strndup(const char *s1, int n);
char			*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
void			ft_putstr_return(char const *s, t_save *save);
void			ft_putchar_return(char c, t_save *save);
size_t			ft_strlen(const char *s);
void			ft_putchar(char c);
void			ft_memdel(void **ap);
char			*ft_strrev(char const *s1, int freeit);
char			*ft_itoabase(unsigned long long nb, int base);
void			*ft_memalloc(size_t size);
int				ft_printf(const char *format, ...);
void			ft_checkoptioncharuni(wchar_t *arg, t_save *save);
void			ft_converts_one(va_list test, t_save *save);
void			ft_printuni(t_save *save, wchar_t c);
void			ft_applymasktwo(wchar_t a, t_save *save);
void			ft_applymaskthree(wchar_t a, t_save *save);
void			ft_printuniw(wchar_t c, t_save *save, int length);
void			ft_printuni_two(t_save *save, wchar_t a, int length);
void			ft_putstr_minu(char *str, t_save *save, int test);
int				ft_stockmodif(t_save *save, char *str, int i, int temp);
void			ft_converts(va_list test, t_save *save);
void			ft_convertc(va_list test, t_save *save);
void			ft_apply(va_list test, t_save *save);
void			ft_applyoptiond(char *str, t_save *save, int neg);
void			ft_pasdeplace(t_save *save, int neg, int *size);
void			ft_applyoptiono(char *str, t_save *save, int neg);
void			ft_applyoptionx(char *str, t_save *save);
void			ft_convertx(va_list test, t_save *save);
void			ft_convertdi(va_list test, t_save *save);
void			ft_convertpxou(va_list test, t_save *save);
void			ft_convertp(va_list test, t_save *save);
void			ft_convertpourcent(t_save *save);
char			*ft_checkoptionint(t_save *save, char *str, int *neg);
void			ft_checkoptionchar(t_save *save, char *str);
void			ft_checkoptionchart(t_save *save, char argument);
void			ft_checkoptionuni(t_save *save, int nb);
void			ft_removestruct(t_save *save, int i);
void			ft_unsigned(int arg, t_save *save);

#endif
