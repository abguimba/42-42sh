/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 06:40:47 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			bg_builtin_output(t_jobs *tmp, char *hold)
{
	if (tmp->background != 1)
	{
		ft_putchar('[');
		ft_putnbr(tmp->place);
		ft_putchar(']');
		ft_putchar('+');
		ft_putchar(' ');
		ft_putstr(tmp->name);
		ft_putchar(' ');
		ft_putchar('&');
		ft_putchar('\n');
		continue_job(tmp, 0);
		tmp->background = 1;
	}
	else
		return (errors_bg(tmp->place, 0, hold));
	ft_strdel(&hold);
	return (0);
}

int			bg_continue(t_jobs *tmp, char *hold)
{
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next && tmp->current != 1)
		tmp = tmp->next;
	return (bg_builtin_output(tmp, hold));
}

int			bg_exists(t_jobs *tmp, int mode, char *hold)
{
	int		nb;

	nb = 0;
	if (mode == 1)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		nb = parse_job_sign(g_tracking.g_tab_exec[1]);
		while (tmp->next && tmp->place != nb)
			tmp = tmp->next;
		if (nb == 0)
			return (errors_bg(0, 2, hold));
		else if (nb != 0)
			return (bg_builtin_output(tmp, hold));
	}
	ft_strdel(&hold);
	hold = parse_job_number(g_tracking.g_tab_exec[1]);
	nb = ft_atoi(hold);
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next && tmp->place != nb)
		tmp = tmp->next;
	ft_strdel(&hold);
	return (bg_builtin_output(tmp, hold));
}

int			bg_builtin_parser(t_jobs *tmp, int nb, char *hold)
{
	if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] == '%')
	{
		hold = parse_job_number(g_tracking.g_tab_exec[1]);
		if (hold)
			nb = ft_atoi(hold);
		if (job_exists(parse_job_sign(g_tracking.g_tab_exec[1])))
			return (bg_exists(tmp, 1, hold));
		else if (hold && job_exists(ft_atoi(hold)))
			return (bg_exists(tmp, 2, hold));
		else if (hold)
			return (errors_bg(ft_atoi(hold), 3, hold));
		else
			return (errors_bg(0, 2, hold));
	}
	else if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] != '%')
		return (errors_bg(tmp->place, 2, hold));
	return (bg_continue(tmp, hold));
}

int			bg_builtin(void)
{
	t_jobs	*tmp;
	char	*hold;
	int		nb;

	nb = 0;
	tmp = g_tracking.jobs;
	hold = NULL;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->startback == 1)
		return (errors_bg(0, 5, hold));
	tmp = g_tracking.jobs;
	if (tmp->next)
		return (bg_builtin_parser(tmp, nb, hold));
	errors_bg(0, 4, hold);
	return (1);
}
