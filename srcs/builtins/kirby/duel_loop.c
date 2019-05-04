/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duel_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 01:37:12 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 00:13:10 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_stylish(int i)
{
	char	*file;
	char	*str;
	int		fd;

	file = get_file(i + 4);
	str = NULL;
	if (!file || verify_path_is_valid(file) == -1)
	{
		if (file)
			ft_strdel(&file);
		return ;
	}
	if ((fd = open(file, O_RDWR, 0644)) == -1)
	{
		ft_strdel(&file);
		return ;
	}
	while (get_next_line(fd, &str) > 0)
	{
		ft_putendl(str);
		ft_strdel(&str);
	}
	ft_strdel(&file);
	ft_strdel(&str);
	close(fd);
}

int		duel_loop(void)
{
	fd_set			setfd;
	struct timeval	tv;
	int				retval;

	FD_ZERO(&setfd);
	FD_SET(0, &setfd);
	tv.tv_sec = 0;
	tv.tv_usec = 80000;
	retval = select(0 + 1, &setfd, NULL, NULL, &tv);
	if (retval == 0)
		return (0);
	return (1);
}

int		duel_get_loop(void)
{
	fd_set			setfd;
	struct timeval	tv;
	int				retval;
	char			c;

	while (1)
	{
		FD_ZERO(&setfd);
		FD_SET(0, &setfd);
		tv.tv_sec = 0;
		tv.tv_usec = 500;
		retval = select(0 + 1, &setfd, NULL, NULL, &tv);
		if (retval == 0)
			return (0);
		if (FD_ISSET(0, &setfd))
		{
			read(0, &c, 1);
			if (c == 's')
				return (1);
			if (c == 'l')
				return (2);
		}
	}
}

int		kirby_duel(void)
{
	time_t	start;
	time_t	stop;
	int		i;
	int		a;

	start = time(NULL);
	stop = time(NULL);
	a = 0;
	i = 0;
	if (set_kirby_screen() != 0)
		return (-1);
	print_file(4);
	print_box(4);
	while (stop < (start + 5))
	{
		if (duel_get_loop() == 1)
			i++;
		if (duel_get_loop() == 2)
			a++;
		stop = time(NULL);
	}
	if (a > i)
		return (print_win(3));
	else
		return (print_win(4));
}

int		duel(int i)
{
	if (duel_loop() == 0)
		return (print_win(i));
	else
		return (kirby_duel());
}
