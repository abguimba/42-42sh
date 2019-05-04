/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:23:11 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:39:01 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		digit_or_str(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		if (ft_isdigit(str[i]) == 1)
			return (0);
		if (str[i] == '+' || str[i] == '-')
		{
			i++;
			if (ft_isdigit(str[i]) == 1)
				return (0);
		}
	}
	return (1);
}

int		fc_get_index(char *str)
{
	t_list		*history;
	char		*buf;
	int			i;

	if (!g_tracking.mysh->hist)
		return (fc_error(4, str));
	if (!str || eq_sign(str) > 0)
		return (-42);
	history = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (fc_error(4, str));
	i = ft_strlen(str);
	while (history)
	{
		buf = history->content;
		if (ft_strncmp(str, buf, i) == 0)
			return (history->index);
		history = history->prev;
	}
	return (fc_error(4, str));
}

void	rev_list(t_fcparse *opt)
{
	int		tmp;

	if (!opt)
		return ;
	tmp = opt->low;
	opt->low = opt->max;
	opt->max = tmp;
	tmp = opt->r;
	if (tmp == 1)
		opt->r = 0;
	if (tmp == 0)
		opt->r = 1;
}

int		transform_nbr(char *nbr)
{
	int		nb;

	if (!nbr)
		return (-1);
	nb = ft_atoi(nbr);
	if (nb > 0)
		nb--;
	return (nb);
}

void	char_to_index(t_fcparse *opt)
{
	int		tmp;

	tmp = 0;
	if (digit_or_str(opt->first) == 0)
		opt->low = transform_nbr(opt->first);
	else
	{
		if (eq_sign(opt->first) == 1)
		{
			if (opt->s != 1)
				fc_error(5, NULL);
			else
				opt->low = -4;
		}
		else
			opt->low = fc_get_index(opt->first);
	}
	if (digit_or_str(opt->last) == 0)
		opt->max = transform_nbr(opt->last);
	else
		opt->max = fc_get_index(opt->last);
	if (opt->low > opt->max && opt->s != 1)
		rev_list(opt);
}
