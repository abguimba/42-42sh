/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 01:52:42 by mjose             #+#    #+#             */
/*   Updated: 2019/03/15 03:27:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
					|| c == '\r')
		return (1);
	return (0);
}

void	unquote(char **value, int *quote)
{
	char	*scan;
	int		type;

	scan = *value;
	type = *quote;
	if (*scan == '\'')
	{
		if (type != '"')
		{
			scan++;
			type = '\'';
		}
	}
	else if (*scan == '"')
	{
		if (type != '\'')
		{
			scan++;
			type = '"';
		}
	}
	*value = scan;
	*quote = type;
}

int		quote_error(char *scan, int open_key, int quote)
{

	if (quote && open_key && ft_iswhitespace(*scan))
		return ('E');
	else if (*scan == '{' && ft_iswhitespace(*(scan + 1)))
		return ('E');
	return (quote);
}

void	reassign_value(char **value, char *new_value, int quote)
{
	if (quote != 'E')
	{
		ft_strdel(value);
		*value = new_value;
	}
}

t_unquoter	*new_unquoted_value(void)
{
	t_unquoter	*value;

	value = (t_unquoter *)malloc(sizeof(t_unquoter));
	value->str_unquoted = NULL;
	value->type = '\0';
	value->next = (t_unquoter *)malloc(sizeof(t_unquoter));
	value->next->str_unquoted = NULL;
	value->next->next = NULL;
	return (value);
}

void	copy_to_quote(char **old, char **new, char *type)
{
	char	*run_old;
	char	*run_new;

	run_old = *old;
	run_new = *new;
	while (*run_old && *run_old != '\'' && *run_old != '"')
		*(run_new++) = *(run_old++);
	if (*run_old && *run_old == '\'')
		*type = '\'';
	else if (*run_old && *run_old == '"')
		*type = '"';
	else
		*type = '\0';
	*old = run_old;
}

void	copy_new_value(char **old, t_unquoter **new)
{
	char		*run_old;
	char		*run_new;
	t_unquoter	*unq_new;

	run_old = *old;
	unq_new = *new;
	run_new = unq_new->str_unquoted;

	if (*run_old)
	{
		if (!unq_new->type)
			copy_to_quote(&run_old, &run_new, &unq_new->next->type);
		else
			while (*run_old && *run_old != unq_new->type)
				*(run_new++) = *(run_old++);
		if (*run_old)
			*old = run_old + 1;
		else
			*old = run_old;
	}
}

t_unquoter	*unquote_value(char **value)
{
	char		*new_value;
	char		*scan;
	int			i;
	int			open_key;
	int			orig_quote;
	t_unquoter	*to_unquot;
	t_unquoter	*first;
	char		next_quote;

//	scan = ft_strdup(*value);
	scan = *value;
	to_unquot = new_unquoted_value();
//	to_unquot->type = '\0';
	to_unquot->error = 0;
	first = to_unquot;
	while (*scan)
	{
		to_unquot->str_unquoted = ft_strnew(ft_strlen(scan));
		if (!to_unquot->type)
			if (*scan && (*scan == '\'' || *scan == '"'))
			{
				to_unquot->type = *scan;
				scan++;
			}
		copy_new_value(&scan, &to_unquot);
		if (*scan && *scan + 1)
		{
			next_quote = to_unquot->next->type;
			if (next_quote < 0)
				next_quote = '\0';
			to_unquot->next = new_unquoted_value();
			to_unquot = to_unquot->next;
			to_unquot->type = next_quote;
		}
	}
/*	new_value = ft_strnew(ft_strlen(*value));
	i = 0;
	open_key = 0;
	while (*scan != '\0')
	{
		unquote(&scan, &quote);
		if (*scan == '{' && !ft_iswhitespace(*(scan + 1)))
			open_key++;
		else if (open_key == 1 && *scan == '}')
			open_key = 0;
		else if ((quote = quote_error(scan, open_key, quote)) == 'E')
			break ;
		if (*scan != '"' && *scan != '\'')
			new_value[i++] = *scan;
		if (*scan)
			scan++;
	}
	reassign_value(value, new_value, quote);
*/	return (first);
}
