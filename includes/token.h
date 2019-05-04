/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:22:50 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 00:05:16 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define PO line[*i] && line[*i] == '('
# define PF line[*i] && line[*i] == ')'
# define GO line[*i] == '"'
# define CMD 1
# define OPT 2
# define ARG 3
# define FICH 4
# define OP 5
# define SEP 6
# define DESCR 7
# define PATH 8

typedef struct	s_last
{
	int				check;
	int				type;
	char			*name;
	struct s_last	*next;
	struct s_last	*prev;
}				t_last;

#endif
