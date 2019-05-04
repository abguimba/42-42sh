/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 01:23:51 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 00:41:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	delete_letter_expand(t_expand **letter)
{
	t_expand	*prev;
	t_expand	*next;

	prev = (*letter)->prev;
	next = (*letter)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (next)
		*letter = next;
	else
		*letter = NULL;
}

void	delete_list_expand(t_expand **letter)
{
	t_expand	*next;

	next = NULL;
	while (*letter && (*letter)->next)
	{
		if ((*letter)->next)
			next = (*letter)->next;
		delete_letter_expand(letter);
		if (next)
			*letter = next;
		else
			*letter = NULL;
	}
	*letter = NULL;
}

void	update_envp(void)
{
	int		i;

	i = 0;
	while (g_tracking.mysh->tab_env[i])
		ft_strdel(&g_tracking.mysh->tab_env[i++]);
	if (g_tracking.mysh->tab_env)
		ft_free(g_tracking.mysh->tab_env);
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
}

void	clean_value(char **value, int unq)
{
	if (*value[0] == '\0' && !g_tracking.mysh->err_expend && unq != 3)
		ft_strdel(value);
	else if (*value[0] == '\0' && !g_tracking.mysh->err_expend
			&& g_tracking.mysh->is_expanded)
		ft_strdel(value);
}
