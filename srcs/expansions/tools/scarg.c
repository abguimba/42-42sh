/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scarg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 01:03:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 07:20:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void		expand_lstdel(t_expand *expan_head)
{
	t_expand	*element;
	t_expand	*next;

	if (expan_head == NULL)
		return ;
	element = expan_head;
	while ((void *)element != NULL)
	{
		next = element->next;
		ft_memdel((void *)&element);
		element = next;
	}
	ft_memdel((void *)&element);
	ft_memdel((void *)&next);
}

void		prepare_to_next_scan(t_scan_arg *scarg)
{
	int		len;

	if (!scarg->new_arg)
		scarg->new_arg = ft_strnew(1);
	len = ft_strlen(scarg->scan->sstring);
	if (len == 1 && !g_tracking.mysh->err_expend
			&& *scarg->scan->sstring == ' ')
		scarg->scan->sstring[0] = '\0';
	scarg->new_arg = ft_strjoinfree(scarg->new_arg, scarg->scan->sstring, 1);
	scarg->scan = scarg->scan->next;
	scarg->expand = NULL;
}

void		expan_arg(t_scan_arg *scarg)
{
	t_expand	*expan_head;

	if ((scarg->scan->sstring[0] != '~' && !scarg->checker->type)
			|| scarg->scan->sstring[0] == '$')
	{
		scarg->expand = new_expand(ft_strlen(scarg->scan->sstring));
		expan_head = scarg->expand;
		create_list_expand(scarg->expand, scarg->scan->sstring);
		transform(scarg->expand, &scarg->scan->sstring);
		expand_lstdel(expan_head);
		expan_head = NULL;
	}
	else if (scarg->scan->sstring[0] == '~')
	{
		scarg->expand = new_expand(ft_strlen(scarg->scan->sstring));
		expan_head = scarg->expand;
		create_list_expand(scarg->expand, scarg->scan->sstring);
		if (!scarg->new_arg)
			transform_if_tilde(&scarg->expand, &scarg->scan->sstring);
		expand_lstdel(expan_head);
	}
	prepare_to_next_scan(scarg);
}

void		fill_scarg(t_scan_arg *scarg)
{
	t_scan		*scan_head;

	scarg->scan = new_scan();
	scan_head = scarg->scan;
	scarg->first_scan = scarg->scan;
	scan_argument(scarg->checker->str_unquoted, scarg->scan);
	scarg->new_arg = NULL;
	while (scarg->scan && scarg->scan->sstring)
		expan_arg(scarg);
	while (scarg->first_scan->sstring)
	{
		ft_strdel(&scarg->first_scan->sstring);
		ft_memdel((void **)scarg->first_scan);
		scarg->first_scan = scarg->first_scan->next;
	}
	if (scarg->new_arg)
	{
		ft_strdel(&scarg->checker->str_unquoted);
		scarg->checker->str_unquoted = scarg->new_arg;
	}
	scan_lstdel(scan_head);
}
