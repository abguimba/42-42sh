/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 00:11:42 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	reset_all(void)
{
	cursor_reset();
}

void	init_global(void)
{
	g_tracking.mysh->err_expend = 0;
	g_tracking.mysh->in_ast = 0;
	g_tracking.mysh->in_here = 0;
	g_tracking.mysh->err_expend_printed = 0;
	g_tracking.builtin = 0;
	g_tracking.jobs = NULL;
	g_tracking.lastreturn = 0;
	g_tracking.expandreturn = 0;
	g_tracking.mysh->hist = NULL;
	g_tracking.mysh->alias_lst = NULL;
	g_tracking.g_tab_exec = NULL;
	g_tracking.prompt = NULL;
	g_tracking.cwd = NULL;
	g_tracking.user = NULL;
	g_tracking.cwd = NULL;
	g_tracking.herenbr = 0;
	g_tracking.herexpnd = 0;
	if (!(g_tracking.aliasloop = ft_malloc(sizeof(t_alias))))
		ft_exit2(EXIT_FAILURE);
	g_tracking.aliasloop->alias = NULL;
	g_tracking.aliasloop->next = NULL;
	g_tracking.mysh->tmpenvsave = NULL;
	g_tracking.mysh->setsave = NULL;
	g_tracking.lastbackground = 0;
	g_tracking.mysh->is_expanded = 0;
}

void	bad_alloc(void)
{
	ft_putendl("Failed to allocate memory");
	ft_exit2(EXIT_FAILURE);
}

void	init_shell(char **environ)
{
	t_shell		*mysh;
	int			i;

	i = 0;
	if (!(mysh = ft_malloc(sizeof(t_shell))))
		bad_alloc();
	while (i++ < 27)
		g_tracking.hashtable[i] = NULL;
	g_tracking.cwd = NULL;
	g_tracking.mysh = mysh;
	init_global();
	init_alias(-1, NULL);
	g_tracking.mysh->env = ft_env_to_lst(environ);
	g_tracking.mysh->hist = NULL;
	add_missing_string();
	if (write(0, "c", 0) != -1)
		hist_file_to_lst(NULL, NULL, -1);
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->set_env = NULL;
	g_tracking.mysh->dup1 = 14;
	g_tracking.mysh->dup2 = 15;
	g_tracking.mysh->dup3 = 16;
	g_tracking.quotes = 0;
	replace_env_set_str("FCEDIT", "nano");
}
