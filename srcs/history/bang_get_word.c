/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_get_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 02:32:26 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 01:27:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_word_alpha(char *word)
{
	t_list	*tmp;
	char	*buf;
	int		i;

	if (!g_tracking.mysh->hist)
		return (return_error_bang());
	tmp = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!tmp || !word)
		return (return_error_bang());
	i = ft_strlen(word);
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strncmp(buf, word, i) == 0)
			return (buf);
		tmp = tmp->prev;
	}
	return (return_error_bang());
}

char	*get_index(char *word)
{
	t_list	*tmp;
	char	*buf;
	size_t	i;

	if (!g_tracking.mysh->hist)
		return (return_error_bang());
	tmp = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!tmp || !word || ft_isinteg(word) != 0)
		return (return_error_bang());
	i = ft_atoi(word) - 1;
	while (tmp)
	{
		buf = tmp->content;
		if (i == tmp->index)
			return (buf);
		tmp = tmp->prev;
	}
	return (return_error_bang());
}

char	*double_bang(void)
{
	t_list	*tmp;
	char	*buf;

	if (!g_tracking.mysh->hist)
		return (return_error_bang());
	tmp = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!tmp)
		return (return_error_bang());
	if (!tmp)
		return (return_error_bang());
	buf = tmp->content;
	return (buf);
}

char	*get_neg(char *word)
{
	t_list	*tmp;
	char	*buf;
	int		i;

	if (!g_tracking.mysh->hist)
		return (NULL);
	tmp = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!tmp || !word || ft_isinteg(word) != 0)
		return (NULL);
	i = ft_atoi(word);
	while (tmp && i < 0)
	{
		buf = tmp->content;
		tmp = tmp->prev;
		if (!tmp)
			return (return_error_bang());
		i++;
	}
	if (!buf)
		return (return_error_bang());
	return (buf);
}

char	*get_word(char *word)
{
	if (!word)
		return (NULL);
	if (ft_isalpha(word[0]) == 1)
		return (get_word_alpha(word));
	if (ft_isdigit(word[0]) == 1 && word[0] != '-')
		return (get_index(word));
	if (word[0] == '-')
		return (get_neg(word));
	if (ft_strcmp(word, "!!") == 0)
		return (double_bang());
	return (NULL);
}
