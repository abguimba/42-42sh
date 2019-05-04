/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 15:05:03 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 10:13:16 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int				get_next_line(const int fd, char **line);

typedef struct	s_fd
{
	char		*buff;
	int			number;
}				t_fd;

#endif
