/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 22:12:59 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:48:01 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	restore_fd_fc(void)
{
	dup2(g_tracking.mysh->dup1, 0);
	close(g_tracking.mysh->dup1);
	dup2(g_tracking.mysh->dup2, 1);
	close(g_tracking.mysh->dup2);
	dup2(g_tracking.mysh->dup3, 2);
	close(g_tracking.mysh->dup3);
}

int		editor_mode(t_fcparse *opt)
{
	if (opt->low && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = opt->low;
	if (opt->low == -42)
		opt->low = opt->max;
	create_fc_file(opt);
	return (0);
}

int		no_edit_mode(t_fcparse *opt)
{
	if (opt->low == -5 && opt->max == -42)
		opt->max = -1;
	if (opt->low == -42 && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	if (opt->low == -1 && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	create_fc_oldnew(opt);
	restore_fd_fc();
	return (0);
}

int		list_mode(t_fcparse *opt)
{
	if (opt->low && opt->max == -42)
	{
		opt->low = -15;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = -1;
	print_fc(opt);
	hist_set_unset(1, opt);
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if ((opt->e == 1 && opt->s == 1) || (opt->e == 1 && opt->l == 1))
		return (fc_error(3, NULL));
	if ((opt->l == 1 && opt->s == 1) || (opt->l == 1 && opt->e == 1))
		return (fc_error(3, NULL));
	if ((opt->s == 1 && opt->n == 1) || (opt->e == 1 && opt->n == 1))
		return (fc_error(3, NULL));
	if (opt->e == 1)
		return (editor_mode(opt));
	if (opt->s == 1)
		return (no_edit_mode(opt));
	if (opt->l == 1)
		return (list_mode(opt));
	return (editor_mode(opt));
}
