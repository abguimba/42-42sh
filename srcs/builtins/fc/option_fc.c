/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_fc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:23:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 06:57:38 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			fc_error(int i, char *str)
{
	if (i == 1)
		ft_putendl_fd("Too many arguments", 2);
	if (i == 2)
		ft_putendl_fd("Invalid option", 2);
	if (i == 3)
		ft_putendl_fd("Incompatible option", 2);
	if (i == 4)
	{
		ft_putstr_fd("Argument out of history range :", 2);
		ft_putendl_fd(str, 2);
		return (-42);
	}
	return (1);
}

t_fcparse	*init_opt(void)
{
	t_fcparse	*opt;

	opt = ft_malloc(sizeof(t_fcparse));
	if (!opt)
		return (NULL);
	opt->e = 0;
	opt->err = 0;
	opt->i = 0;
	opt->s = 0;
	opt->r = 0;
	opt->n = 0;
	opt->l = 0;
	opt->low = 0;
	opt->max = 0;
	opt->str = NULL;
	opt->editor = NULL;
	opt->first = NULL;
	opt->last = NULL;
	opt->shist = NULL;
	return (opt);
}

t_fcparse	*fill_opt(t_fcparse *opt)
{
	int		i;
	char	c;

	i = 0;
	if (!opt || !opt->str)
		return (opt);
	while (opt->str[i])
	{
		c = opt->str[i];
		if (c == 'l')
			opt->l = 1;
		if (c == 'e')
			opt->e = 1;
		if (c == 's')
			opt->s = 1;
		if (c == 'n')
			opt->n = 1;
		if (c == 'r')
			opt->r = 1;
		if (c != 'l' && c != 'r' && c != 'n' && c != 'e' && c != 's')
			opt->err = 1;
		i++;
	}
	return (opt);
}

t_fcparse	*fc_option(char **av, int i)
{
	t_fcparse	*opt;
	char		*tmp;

	i = 1;
	if ((opt = init_opt()) == NULL)
		return (NULL);
	while (av[i] && ft_strcmp(av[i], "--") != 0 && ft_isinteg(av[i]) != 0)
	{
		if (ft_strcmp(av[i - 1], "-e") == 0)
			opt->editor = ft_strdup(av[i]);
		else
		{
			if (av[i][0] != '-')
				break ;
			tmp = ft_strsub(av[i], 1, ft_strlen(av[i]), 0);
			opt->str = ft_strjoinfree(opt->str, tmp, 3);
		}
		i++;
	}
	if (ft_strcmp(av[i], "--") == 0)
		i++;
	opt->i = i;
	if (opt->str)
		opt = fill_opt(opt);
	return (opt);
}

t_fcparse	*fc_offset(char **av, t_fcparse *opt)
{
	int		i;

	i = opt->i;
	if (!av)
		return (NULL);
	if (av[i])
	{
		opt->first = ft_strdup(av[i]);
		i++;
	}
	if (av[i])
	{
		opt->last = ft_strdup(av[i]);
		i++;
	}
	if (av[i])
	{
		fc_error(1, NULL);
		return (NULL);
	}
	return (opt);
}
