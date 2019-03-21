/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 04:28:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		single_key(char c)
{
	if (c == K_BKSP)
	{
		rem_from_str();
		return (12);
	}
	if (c == K_CTRLR)
	{
		begin_search();
		return (12);
	}
	if (c == 10 || c == 13)
	{
		ft_return();
		return (13);
	}
	if (c == K_TAB)
	{
		auto_complete();
		return (12);
	}
	return (ctrl_key(c));
}

int		check(char *str)
{
	if (ft_strncmp(str, "\x1b\x5b", 2) == 0
	|| ft_strncmp(str, "\x1b\x4f", 2) == 0)
		return (1);
	return (0);
}

int		return_loop(int i, char *str)
{
	if (check(str) == 1 || i == 12 || i == 6)
		free(str);
	else
		add_to_str(str);
	return (0);
}

int		readloop(int i, int fd)
{
	char	c;
	char	*str;

	str = ft_strnew(0);
	if ((read(fd, &c, 1)) == 0)
		ft_exit();
	str = ft_strjoinchar(str, c, 1);
	i = single_key(c);
	if (i == 13 || i == 10)
	{
		free(str);
		return (1);
	}
	if (c < 32 && i != 12)
	{
		while (42)
		{
			read(STDERR_FILENO, &c, 1);
			str = ft_strjoinchar(str, c, 1);
			i = is_cmd(str);
			if (i >= 6)
				break ;
		}
	}
	return (return_loop(i, str));
}

void	test_read(void)
{
	char	c[12];
	int		i;

	i = 0;
	read(STDERR_FILENO, &c, 12);
	while (c[i])
	{
		printf("0x%x\n", c[i]);
		if (i != 6)
			ft_putchar('.');
		else
			ft_putchar('\n');
		i++;
	}
}


int		get_key(void)
{
	char	*str;

	tcsetattr(0, TCSANOW, &g_tracking.myterm);
	get_coolprompt();
	if (g_tracking.interactive == 1)
		print_prompt();
	g_tracking.histindex = get_last() + 1;
	if (g_tracking.linemode == 0)
	{
		while (readloop(0, STDIN_FILENO) == 0)
		{
		}
	}
	else
	{
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		get_next_line(0, &str);
		g_tracking.cmd = ft_strdup(str);
		g_tracking.str = NULL;
		free(str);
		str = NULL;
	}
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	return (1);
}
