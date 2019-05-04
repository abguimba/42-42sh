/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 00:46:35 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

t_expand	*new_expand(int len)
{
	t_expand	*new_letter;

	new_letter = ft_memalloc(sizeof(t_expand));
	new_letter->ltr = '\0';
	new_letter->len = len;
	new_letter->idx = 0;
	new_letter->next = NULL;
	new_letter->prev = NULL;
	return (new_letter);
}

void		create_list_expand(t_expand *new_letter, char *line)
{
	int			i;
	int			len;
	t_expand	*frst_letter;
	t_expand	*prev_letter;

	i = 0;
	len = new_letter->len;
	frst_letter = new_letter;
	while (line && line[i])
	{
		new_letter->ltr = line[i];
		new_letter->idx = i + 1;
		if (line[i + 1])
		{
			prev_letter = new_letter;
			new_letter->next = new_expand(len);
			new_letter = new_letter->next;
			new_letter->prev = prev_letter;
			i++;
		}
		else
			break ;
	}
	new_letter = frst_letter;
}

void		scan_arg_transformer(t_unquoter **check, char **value)
{
	t_scan_arg	scarg;
	char		*rest_of;

	scarg.checker = *check;
	scarg.new_arg = NULL;
	while (scarg.checker && scarg.checker->str_unquoted)
	{
		rest_of = ft_strdup(ft_strchr(scarg.checker->str_unquoted, 92));
		if (scarg.checker->type != '\'')
			fill_scarg(&scarg);
		if (rest_of && !ft_strchr(scarg.checker->str_unquoted, 92))
			scarg.checker->str_unquoted = ft_strjoinfree(
				scarg.checker->str_unquoted, rest_of, 1);
		scarg.checker = scarg.checker->next;
		ft_strdel(&rest_of);
	}
	scarg.checker = *check;
	ft_strdel(value);
	*value = ft_strnew(1);
	while (scarg.checker->str_unquoted)
	{
		*value = ft_strjoinfree(*value, scarg.checker->str_unquoted, 1);
		scarg.checker = scarg.checker->next;
	}
}

void		mark_to_remove(t_unquoter *to_unquot, char **value)
{
	if (ft_strequ(to_unquot->str_unquoted, "${}"))
		print_exp_error(NULL, value);
	else if (!g_tracking.mysh->in_here)
		print_exp_invalid(to_unquot->str_unquoted);
}

char		expand_transformer(char **value, int unq)
{
	char		*str_orig;
	t_unquoter	*to_unquot;
	t_unquoter	*first;

	to_unquot = NULL;
	g_tracking.mysh->is_expanded = 0;
	to_unquot = unquote_value(value);
	first = to_unquot;
	first = unquoter_prepare(to_unquot);
	to_unquot = first;
	str_orig = ft_strdup(*value);
	if (to_unquot && unq != 2 && (!ft_strstr(to_unquot->str_unquoted, "${}")
			|| !ft_strstr(to_unquot->str_unquoted, "${}")))
		scan_arg_transformer(&to_unquot, value);
	else if ((to_unquot && ft_strequ(to_unquot->str_unquoted, "${}"))
			|| ft_strequ(str_orig, "${}")
			|| ft_strstr(to_unquot->str_unquoted, "${}"))
		mark_to_remove(to_unquot, value);
	ft_strdel(&str_orig);
	if (!unq)
		quotenize(first, value);
	clean_value(value, unq);
	clean_unquoter(first);
	return (0);
}
