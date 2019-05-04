/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coolprompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 23:51:02 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			transform_cwd(int i)
{
	char		*home;
	int			l;
	char		*n;

	home = ft_strdup(get_env_string("HOME"));
	if (ft_strstr(g_tracking.cwd, home))
	{
		l = ft_strlen(home);
		if (!(n = ft_malloc(sizeof(char) * ft_strlen(g_tracking.cwd) - l + 2)))
			return ;
		l = l + 2;
		n[i++] = '<';
		n[i++] = ' ';
		n[i++] = '~';
		while (g_tracking.cwd[l] != '\0')
		{
			n[i++] = g_tracking.cwd[l];
			l++;
		}
		n[i] = '\0';
		ft_strdel(&g_tracking.cwd);
		g_tracking.cwd = NULL;
		g_tracking.cwd = n;
	}
	ft_free(home);
}

void			set_prompt_quote(void)
{
	char		*memory;

	memory = g_tracking.prompt;
	if (g_tracking.quotes == 1)
	{
		g_tracking.prompt = ft_strdup("dquotes >");
		ft_strdel(&memory);
		memory = NULL;
	}
	if (g_tracking.quotes == 2)
	{
		g_tracking.prompt = ft_strdup("quotes >");
		ft_strdel(&memory);
		memory = NULL;
	}
	if (g_tracking.quotes == 3)
	{
		g_tracking.prompt = ft_strdup(">");
		ft_strdel(&memory);
		memory = NULL;
	}
	g_tracking.pos->prompt = utf_strlen(g_tracking.prompt);
	ft_strdel(&memory);
	memory = NULL;
}

void			print_prompt(void)
{
	if (g_tracking.quotes == 1
			|| g_tracking.quotes == 2 || g_tracking.quotes == 3)
	{
		ft_putstr_fd(ANSI_COLOR_RED, 2);
		ft_putstr_fd(g_tracking.prompt, 2);
		ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
		return ;
	}
	ft_putstr_fd(ANSI_COLOR_BLUE, 2);
	ft_putstr_fd(g_tracking.user, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(ANSI_COLOR_MAGENTA, 2);
	ft_putstr_fd(g_tracking.cwd, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
	ft_putchar_fd(' ', 2);
	if (g_tracking.lastreturn != 0)
		ft_putstr_fd(ANSI_COLOR_RED, 2);
	else
		ft_putstr_fd(ANSI_COLOR_GREEN, 2);
	ft_putstr_fd(g_tracking.prompt, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
}

void			get_coolprompt_cont(int mode, char *prompt)
{
	int			i;

	i = 0;
	if (mode == 1)
		g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, "No environment", 1);
	g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, " >", 1);
	if (get_env_string("HOME"))
		transform_cwd(i);
	prompt = ft_strdup(SHELL_NAME);
	prompt = ft_strjoinfree(prompt, " $/> ", 1);
	ft_strdel(&g_tracking.prompt);
	g_tracking.prompt = NULL;
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = utf_strlen(prompt) + utf_strlen(g_tracking.cwd);
	g_tracking.pos->prompt += utf_strlen(g_tracking.user);
	g_tracking.pos->prompt += 2;
	ft_strdel(&prompt);
}

void			get_coolprompt(void)
{
	char		*prompt;
	char		*buff;

	prompt = NULL;
	ft_strdel(&g_tracking.prompt);
	ft_strdel(&g_tracking.cwd);
	g_tracking.cwd = NULL;
	ft_strdel(&g_tracking.user);
	if (g_tracking.quotes >= 1 && g_tracking.quotes <= 3)
		return (set_prompt_quote());
	g_tracking.user = ft_strdup("[");
	g_tracking.user = ft_strjoinfree(g_tracking.user, getlogin(), 1);
	g_tracking.user = ft_strjoinfree(g_tracking.user, "]", 1);
	g_tracking.cwd = ft_strdup("< ");
	if (get_env_string("PWD"))
	{
		buff = get_env_string("PWD");
		g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, buff, 1);
		return (get_coolprompt_cont(2, prompt));
	}
	return (get_coolprompt_cont(1, prompt));
}
