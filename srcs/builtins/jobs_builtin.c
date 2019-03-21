/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:29:23 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			jobs_builtin_options(t_jobs *tmp, int options, int i, char **t)
{
	char	*hold;
	int		j;

	hold = NULL;
	j = options;
	if (t[i] && t[i][0] == '%')
	{
		while (t[i] && t[i][0] == '%')
		{
			hold = parse_job_number(t[i]);
			if (job_exists(parse_job_sign(t[i])))
				jobs_builtin_output(tmp, 1, parse_job_sign(t[i]), j);
			else if (hold && job_exists(ft_atoi(hold)))
				jobs_builtin_output(tmp, 1, ft_atoi(hold), j);
			else if (hold)
				errors_jobs('a', ft_atoi(hold), 2);
			else
				errors_jobs('a', 0, 2);
			i++;
		}
	}
	else
		jobs_builtin_output(tmp, 0, 0, j);
	return (0);
}

int			jobs_builtin_parser(t_jobs *tmp, int i, int options, char **t)
{
	int		j;

	if (t[i])
	{
		while (t[i] && t[i][0] == '-')
		{
			if (!t[i][1])
				return (errors_jobs('a', 0, 0));
			j = 1;
			while (t[i][j] != '\0')
			{
				if (t[i][j] != 'l' && t[i][j] != 'p')
					return (errors_jobs(t[i][j], 0, 1));
				else if (t[i][j] == 'l')
					options = 1;
				else if (t[i][j] == 'p')
					options = 2;
				j++;
			}
			i++;
		}
		return (jobs_builtin_options(tmp, options, i, t));
	}
	jobs_builtin_output(tmp, 0, 0, 0);
	return (0);
}

void		jobs_builtin_mode(t_jobs *tmp, int mode, int options, int number)
{
	if (options != 2)
	{
		if (tmp->background == 1)
			ft_putstr("Running           ");
		if (options != 1 && tmp->t_command->stopped == 1)
			ft_putstr("Stopped           ");
		else if (options == 1)
			ft_putstr("Suspended           ");
		else
			ft_putstr("       ");
		ft_putstr(tmp->name);
		if (tmp->background == 1)
			ft_putstr(" &");
		ft_putstr("      ");
		if (ft_strcmp(tmp->wd, getcwd(NULL, 42)))
		{
			ft_putstr("(wd: ");
			ft_putstr(tmp->wd);
			ft_putendl(")  ");
		}
		else
			ft_putchar('\n');
		if (mode == 1 && tmp->place == number)
			return ;
	}
}

void		jobs_builtin_output(t_jobs *tmp, int mode, int number, int options)
{
	while (tmp && tmp->next)
	{
		if (mode == 0 || (mode == 1 && number == tmp->place))
		{
			if (options != 2)
			{
				ft_putchar('[');
				ft_putnbr(tmp->place);
				ft_putchar(']');
				if (tmp->current == 1)
					ft_putstr("+ ");
				else if (tmp->currentback == 1)
					ft_putstr("- ");
				else
					ft_putstr("  ");
			}
			if (options == 1 || options == 2)
				ft_putnbr(tmp->jpid);
			ft_putchar(' ');
			if (options == 2)
				ft_putchar('\n');
			jobs_builtin_mode(tmp, mode, options, number);
		}
		tmp = tmp->next;
	}
}

int			jobs_builtin(void)
{
	t_jobs	*tmp;
	int		options;
	int		i;

	i = 1;
	options = 0;
	tmp = g_tracking.jobs;
	if (tmp && tmp->next)
		return (jobs_builtin_parser(tmp, i, options, g_tracking.g_tab_exec));
	errors_jobs('a', 0, 4);
	return (1);
}
