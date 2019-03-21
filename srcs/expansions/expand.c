/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/03/21 00:21:55 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

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

int			need_expand(char *to_transf)
{
	if (to_transf[0] == '~' && !to_transf[1])
		return (1);
	else if (to_transf[0] && to_transf[1] == '/')
		return (1);
	else if (to_transf[0] == '~' && (to_transf[1] == '+'
			|| to_transf[1] == '-') && (!to_transf[2]
			|| to_transf[2] == '/'))
		return (1);
	else if (is_path_tilde(to_transf))
		return (1);
	else if (to_transf[0] == '~' && have_homedir(to_transf))
		return (1);
	else if (have_parm(to_transf))
		return (1);
	else if (is_to_add_or_mod_parm(to_transf))
		return (1);
	else if (to_transf[0] == '$' && to_transf[1])
		return (1);
	return (0);
}

void		scan_arg_transformer(t_unquoter **check, char **value)
{
	t_expand	*expand;
	t_scan		*scan;
	t_scan		*first_scan;
	t_unquoter	*checker;
	char		*new_arg;
	int			ret;

	checker = *check;
	new_arg = NULL;
	while (checker && checker->str_unquoted)
	{
		if (checker->type != '\'')
		{
			scan = new_scan();
			first_scan = scan;
//		scan_argument(*arg, scan, 0, quote);
			scan_argument(checker->str_unquoted, scan, 0, checker->type);
			new_arg = NULL;
			while (scan && scan->sstring)
			{
				expand = new_expand(ft_strlen(scan->sstring));
				create_list_expand(expand, scan->sstring);
//			if ((scan->sstring[0] != '~' && !quote) || scan->sstring[0] == '$')
				if ((scan->sstring[0] != '~' && !checker->type) || scan->sstring[0] == '$')
				{
//				ret = transform(expand, &scan->sstring);
					checker->error = transform(expand, &scan->sstring);
/*				if (ret == 1)
					return (1);
*/				}
				else if (scan->sstring[0] == '~')
					transform_if_tilde(&expand, &scan->sstring);
				if (!new_arg)
					new_arg = ft_strnew(1);
				new_arg = ft_strjoinfree(new_arg, scan->sstring, 1);
				scan = scan->next;
			}
			while (first_scan->sstring)
			{
				ft_strdel(&first_scan->sstring);
				ft_memdel((void **)first_scan);
				first_scan = first_scan->next;
			}
			if (first_scan)
				ft_memdel((void **)first_scan);
			first_scan = NULL;
			if (new_arg)
			{
				ft_strdel(&checker->str_unquoted);
				checker->str_unquoted = new_arg;
			}
		}
		checker = checker->next;
//		*arg = new_arg;
	}
	checker = *check;
	ft_strdel(value);
	*value = ft_strnew(1);
	while (checker->str_unquoted)
	{
		*value = ft_strjoinfree(*value, checker->str_unquoted, 2);
		checker = checker->next;
	}
//	scan = first_scan;
//	ft_strdel(arg);
//	*arg = new_arg;
//	return (0);
}

char		expand_transformer(char **value, int chg_value)
{
	char		quote;
	char		*str_error;
	t_unquoter	*to_unquot;

	quote = 0;
	str_error = ft_strdup(*value);
	to_unquot = NULL;
//	if (chg_value)
		to_unquot = unquote_value(value);
	if (to_unquot && (!ft_strstr(to_unquot->str_unquoted, "${}")
			|| !ft_strstr(to_unquot->str_unquoted, "${}")))
		scan_arg_transformer(&to_unquot, value);
	else if ((to_unquot && ft_strequ(to_unquot->str_unquoted, "${}"))
			|| ft_strequ(str_error, "${}")
			|| ft_strstr(to_unquot->str_unquoted, "${}"))
	{
		if (ft_strequ(to_unquot->str_unquoted, "${}"))
			print_exp_error(NULL);
		else
			print_exp_str_error(to_unquot->str_unquoted);
		ft_strdel(value);
		*value = ft_strdup(" ");
	}
//		quote = unquote_value(value, quote);
/*	if (quote != '\'' && quote != 'E' && *value)
		quote = scan_arg_transformer(value, quote);
	if (quote == 'E')
	{
		print_exp_error(str_error);
		ft_strdel(value);
		*value = ft_strdup("");
	}
	if (quote == 1)
		*value = ft_strdup("");
	ft_strdel(&str_error);
	return (quote);*/
	return (0);
}
