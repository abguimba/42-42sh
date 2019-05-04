/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:04:25 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:15:06 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	put_unexpected_token(char *sym)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	ft_putstr_fd(sym, 2);
	ft_putendl_fd("'", 2);
}
