/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 05:11:32 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line)
		return (NULL);
	while (nb < (int)ft_strlen(line) && line[nb] && line[nb] == ' ')
	{
		(*i)++;
		nb++;
	}
	if ((test = search_fd_reddir(&line[nb])))
		return (test);
	else if ((test = search_reddir(&line[nb])))
		return (test);
	else if ((test = search_symboll(&line[nb])))
		return (test);
	else
		test = search_normally_arg(&line[nb], i, 0);
	return (test);
}

char	*return_modif_line(char c, char *line)
{
	char	*temp;

	if (c == '"')
	{
		temp = check_quote('"');
		line = ft_strjoinchar(line, '\n', 1);
		line = ft_strjoinfree(line, temp, 3);
		return (line);
	}
	else if (c == '\'')
	{
		temp = check_quote('\'');
		line = ft_strjoinchar(line, '\n', 1);
		line = ft_strjoinfree(line, temp, 3);
		return (line);
	}
	else
	{
		temp = check_bracket(line, 0);
		line = ft_strjoinchar(line, '\n', 1);
		line = ft_strjoinfree(line, temp, 3);
		return (line);
	}
}

char	*ft_modif_line(char *line)
{
	int		flag;

	flag = 0;
	if (ft_valid_quote(line, '"', 0))
	{
		flag = 1;
		line = return_modif_line('"', line);
	}
	else if (ft_valid_quote(line, '\'', 0) && flag == 0)
	{
		flag = 1;
		line = return_modif_line('\'', line);
	}
	else if (ft_valid_bracket(line) && flag == 0)
	{
		flag = 1;
		line = return_modif_line('}', line);
	}
	return (line);
}

void	add_cmd_to_list(int i, char *line, char *temp, t_last **list_cmd)
{
	while (line[i] && (temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		i += ft_strlen(temp);
		(*list_cmd)->next = create_new_list();
		(*list_cmd)->next->prev = *list_cmd;
		*list_cmd = (*list_cmd)->next;
		ft_strdel(&(*list_cmd)->name);
		(*list_cmd)->name = ft_strdup(temp);
		ft_strdel(&temp);
	}
	(*list_cmd)->next = NULL;
	ft_strdel(&temp);
}

t_last	*ft_parseur(int i, char *str, t_last *list_cmd, t_last *templ)
{
	char	*temp;
	char	*line;

	str = convert_backslash(str);
	if (!str)
		return (NULL);
	if (!(line = quote_check(str)))
		return (NULL);
	line = alias_swapper(line, 0, 1);
	while (i < (int)ft_strlen(line) && line[i] && line[i] == ' ')
		i++;
	if ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		i += ft_strlen(temp);
		list_cmd = create_new_list();
		templ = list_cmd;
		list_cmd->name = ft_strdup(temp);
		ft_strdel(&temp);
		add_cmd_to_list(i, line, temp, &list_cmd);
		list_cmd = templ;
		ft_strdel(&line);
	}
	else
		return (ret_error(line));
	return (list_cmd);
}
