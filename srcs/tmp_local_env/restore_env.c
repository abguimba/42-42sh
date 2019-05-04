/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:32:10 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	*m_malloc(int i)
{
	void	*ptr;

	ptr = ft_malloc(sizeof(i));
	if (ptr == NULL)
	{
		ft_putendl("Failed to allocate memory");
		ft_exit2(EXIT_FAILURE);
	}
	return (ptr);
}

void	restore_env(void)
{
	free_keyval(g_tracking.mysh->env);
	g_tracking.mysh->env = ft_env_to_lst(g_tracking.mysh->tab_env);
}
