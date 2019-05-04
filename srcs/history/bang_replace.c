/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 04:46:38 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 09:13:34 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*return_error_bang(void)
{
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Event not found", 2);
	return (NULL);
}

char	*get_keyword(char *line, int i)
{
	int		a;
	char	*word;

	i++;
	a = 0;
	word = ft_strnew(ft_strlen(line));
	if (ft_isalpha(line[i]) == 1)
	{
		while (is_space_ac(line, i) != 1)
			word[a++] = line[i++];
	}
	else
	{
		while (is_space_ac(line, i) != 1 && (line[i] == '-'
			|| ft_isdigit(line[i]) == 1))
			word[a++] = line[i++];
	}
	return (word);
}

char	*return_fail(char *begin, char *end, char *line)
{
	ft_strdel(&begin);
	ft_strdel(&end);
	ft_strdel(&line);
	return (NULL);
}

char	*replace_word(char *line, int i)
{
	int		j;
	char	*end;
	char	*begin;
	char	*word;
	char	*tmp;

	if (!line)
		return (NULL);
	begin = ft_strsub(line, 0, i, 0);
	word = get_keyword(line, i);
	i = i + ft_strlen(word);
	i++;
	j = ft_strlen(line) - i;
	end = ft_strsub(line, i, j, 0);
	tmp = word;
	word = ft_strdup(get_word(word));
	ft_strdel(&tmp);
	if (!word)
		return (return_fail(begin, end, line));
	ft_strdel(&line);
	begin = ft_strjoinfree(begin, word, 3);
	begin = ft_strjoinfree(begin, end, 3);
	return (begin);
}

char	*replace_double(char *line, int i)
{
	int		j;
	char	*end;
	char	*begin;
	char	*word;
	char	*tmp;

	if (!line)
		return (NULL);
	begin = ft_strsub(line, 0, i, 0);
	word = ft_strdup("!!");
	i = i + ft_strlen(word);
	j = ft_strlen(line) - i;
	end = ft_strsub(line, i, j, 0);
	tmp = word;
	word = ft_strdup(get_word(word));
	ft_strdel(&tmp);
	if (!word)
		return (return_fail(begin, end, line));
	ft_strdel(&line);
	begin = ft_strjoinfree(begin, word, 3);
	begin = ft_strjoinfree(begin, end, 3);
	return (begin);
}
