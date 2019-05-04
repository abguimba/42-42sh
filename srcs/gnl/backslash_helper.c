/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 23:13:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 03:35:57 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	reset_char_helper(char c)
{
	if (c == 20)
		return ('{');
	if (c == 21)
		return ('}');
	if (c == 22)
		return ('=');
	if (c == 23)
		return ('~');
	if (c == 24)
		return ('\n');
	return (c);
}

char	get_char_helper(char c)
{
	if (c == '{')
		return (20);
	if (c == '}')
		return (21);
	if (c == '=')
		return (22);
	if (c == '~')
		return (23);
	if (c == '\n')
		return (24);
	return (c);
}
