/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kirby_read_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:44:06 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 00:13:16 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		error_file(char *file)
{
	ft_putendl_fd("Could not access gamefile", 2);
	sleep(2);
	if (file)
		ft_strdel(&file);
	return (-5);
}

int		rand_loop(int a, int b)
{
	fd_set			setfd;
	struct timeval	tv;
	int				retval;
	char			c;

	while (1)
	{
		FD_ZERO(&setfd);
		FD_SET(0, &setfd);
		tv.tv_sec = a;
		tv.tv_usec = b;
		retval = select(0 + 1, &setfd, NULL, NULL, &tv);
		if (retval == 0)
		{
			print_box(2);
			return (0);
		}
		if (FD_ISSET(0, &setfd))
		{
			read(STDERR_FILENO, &c, 1);
			return (too_soon(c));
		}
	}
}

int		generate_rand(void)
{
	int		random;
	int		a;
	int		b;

	random = 0;
	a = 0;
	b = 0;
	srand(time(NULL));
	random = rand() % 3;
	if (random < 1)
	{
		a = 0;
		b = 500000;
	}
	else
	{
		a = random;
		b = 0;
	}
	return (rand_loop(a, b));
}

int		read_samurai(void)
{
	char	c;

	write(2, "\a", 1);
	write(2, "\a", 1);
	c = 0;
	print_box(3);
	read(0, &c, 1);
	if (c == 27)
		return (1);
	if (c == 115)
		return (duel(1));
	if (c == 108)
		return (duel(2));
	return (0);
}

int		game_loop(void)
{
	int		i;

	if (set_kirby_screen() != 0)
		return (-1);
	if (print_usage() == 1)
		return (1);
	if (set_kirby_screen() != 0)
		return (-1);
	if ((print_file(1) == -5))
		return (-1);
	print_box(0);
	i = generate_rand();
	if (i == -3)
		return (0);
	if (i == -1)
		return (1);
	return (read_samurai());
}
