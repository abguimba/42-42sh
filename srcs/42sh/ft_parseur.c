/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 18:15:38 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line)
		return (NULL);
	while (line[nb] == ' ')
	{
		(*i)++;
		nb++;
	}
	if ((test = search_fd_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_symboll(&line[nb], i)))
		return (test);
	else
		test = search_normally_arg(&line[nb], i);
	return (test);
}

void	return_modif_line(char c, char **line)
{
	char	*new_line;
	char	*temp;

	if (c == '"')
	{
		temp = check_quote(*line, 0, '"');
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
	}
	else if (c == '\'')
	{
		temp = check_quote(*line, 0, '\'');
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
	}
	else
	{
		temp = check_bracket(*line, 0);
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
	}
}

char	*ft_modif_line(char **line)
{
	char	*temp;

	temp = NULL;
	if (ft_valid_quote(*line, '"', 0))
	{
		return_modif_line('"', line);
		return (NULL);
	}
	else if (ft_valid_quote(*line, '\'', 0))
	{
		return_modif_line('\'', line);
		return (NULL);
	}
	else if (ft_valid_bracket(*line, '}', 0))
	{
		return_modif_line('}', line);
		return (NULL);
	}
	return (ft_strdup(*line));
}

void	add_cmd_to_list(int i, char *line, char *temp, t_last **list_cmd)
{
	while (line[i] && (temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		i += ft_strlen(temp);
		(*list_cmd)->next = create_new_list();
		(*list_cmd)->next->prev = *list_cmd;
		*list_cmd = (*list_cmd)->next;
		(*list_cmd)->name = ft_strdup(temp);
	}
	(*list_cmd)->next = NULL;
}

t_last	*ft_parseur(char *str)
{
	char	*temp;
	int		i;
	char	*line;
	t_last	*list_cmd;
	t_last	*templist;

	i = 0;
	list_cmd = NULL;
	while (str[i] == ' ')
		i++;
	while ((line = ft_modif_line(&str)) == NULL)
		;
	if ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		i += ft_strlen(temp);
		list_cmd = create_new_list();
		templist = list_cmd;
		list_cmd->name = temp;
		temp = NULL;
		add_cmd_to_list(i, line, temp, &list_cmd);
		list_cmd = templist;
	}
	else
		return (NULL);
	return (list_cmd);
}
