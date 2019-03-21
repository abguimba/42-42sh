/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:29:52 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 04:03:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		yan_putchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void	init_cpaste(void)
{
	g_tracking.cpaste->b1 = 0;
	g_tracking.cpaste->b2 = 0;
	g_tracking.cpaste->line = NULL;
}

void	init_key_list(void)
{
	g_tracking.key_list = lstcontainer_new();
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LEFT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_RIGHT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DOWN));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_UP));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LUP));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LDOWN));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_WLEFT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_WRIGHT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DEL));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_ESC));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_FN1));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_FN2));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_FN3));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_HOME));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_END));
}

void	cursor_reset(void)
{
	g_tracking.pos->abs = 0;
	g_tracking.pos->x = 1;
	g_tracking.pos->y = 0;
	g_tracking.pos->relx = 1;
	g_tracking.pos->rely = 0;
	g_tracking.pos->legacy = 0;
	g_tracking.swi = 0;
	g_tracking.cpaste = malloc(sizeof(t_cpaste));
	g_tracking.cpaste->line = NULL;
	g_tracking.buffsize = 2;
	g_tracking.search = NULL;
	g_tracking.found = NULL;
	g_tracking.quotes = 0;
	g_tracking.herenbr = 0;
	if ((g_tracking.str = malloc(sizeof(char) * g_tracking.buffsize)) == NULL)
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	ft_bzero(g_tracking.str, g_tracking.buffsize);
}

void	cursorinit(void)
{
	if ((g_tracking.pos = malloc(sizeof(t_cursor) + 1)) == NULL)
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	cursor_reset();
	init_key_list();
}
