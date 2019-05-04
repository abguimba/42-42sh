/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:27:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 06:41:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*get_file(int i)
{
	char	*file;

	file = NULL;
	file = ft_strdup(get_set_env_string("kirby"));
	if (!file)
		return (NULL);
	if (i == 1)
		file = ft_strjoinfree(file, "/kirby/sprite1v2.txt", 1);
	if (i == 2)
		file = ft_strjoinfree(file, "/kirby/sprite2v2.txt", 1);
	if (i == 3)
		file = ft_strjoinfree(file, "/kirby/sprite3v2.txt", 1);
	if (i == 4)
		file = ft_strjoinfree(file, "/kirby/clash.txt", 1);
	if (i == 5)
		file = ft_strjoinfree(file, "/kirby/stylish1.txt", 1);
	if (i == 6)
		file = ft_strjoinfree(file, "/kirby/stylish2.txt", 1);
	return (file);
}

char	*get_box_file(int i)
{
	char	*file;

	file = NULL;
	file = ft_strdup(get_set_env_string("kirby"));
	if (!file)
		return (NULL);
	if (i == 0)
		file = ft_strjoinfree(file, "/kirby/Ready.txt", 1);
	if (i == 1)
		file = ft_strjoinfree(file, "/kirby/P1wins.txt", 1);
	if (i == 2)
		file = ft_strjoinfree(file, "/kirby/P2wins.txt", 1);
	if (i == 3)
		file = ft_strjoinfree(file, "/kirby/GO.txt", 1);
	if (i == 4)
		file = ft_strjoinfree(file, "/kirby/DUEL.txt", 1);
	return (file);
}
