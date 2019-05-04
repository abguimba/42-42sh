/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 03:09:44 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 00:15:58 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

char		*back_slash_error(char *str)
{
	str = convert_back(str);
	print_exp_invalid(str);
	str = convert_backslash(str);
	return (str);
}

t_unquoter	*new_unquoted_value(void)
{
	t_unquoter	*value;

	value = (t_unquoter *)ft_malloc(sizeof(t_unquoter));
	value->str_unquoted = NULL;
	value->type = '\0';
	value->intra_key = 0;
	value->next = (t_unquoter *)ft_malloc(sizeof(t_unquoter));
	value->next->str_unquoted = NULL;
	value->next->type = '\0';
	value->next->next = NULL;
	return (value);
}

void		copy_to_quote(char **old, char **new, char *type)
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

void		copy_new_value(char **old, t_unquoter **new)
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

t_unquoter	*quote_checker(t_unquoter *to_unquot, char **ascan)
{
	char	*cscan;

	cscan = *ascan;
	to_unquot->str_unquoted = ft_strnew(ft_strlen(cscan));
	if (!to_unquot->type)
		if (*cscan && (*cscan == '\'' || *cscan == '"'))
		{
			to_unquot->type = *cscan;
			cscan++;
		}
	copy_new_value(&cscan, &to_unquot);
	*ascan = cscan;
	return (to_unquot);
}
