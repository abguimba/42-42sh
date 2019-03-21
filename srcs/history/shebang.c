/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/20 03:24:10 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*shebang_last(char *line, char *last_line)
{
	char *nline;
	t_hist *hist;
	int i;

	i = 0;
	hist = g_tracking.mysh->hist;
	// hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	while (hist->next)
		hist = hist->next;
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return nline;
}

char	*shebang_word(char *line, char *last_line)
{
	char *nline;
	int i;
	t_hist *hist;

	i = 0;
	hist = g_tracking.mysh->hist;
	// hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	while (hist->previous && ft_strncmp(hist->line, line, i) != 0)
		hist = hist->previous;
	if ((!hist->previous && ft_strncmp(hist->line, line, i) != 0) || i == 0)
		{
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return nline;
}

char	*shebang_num_pos(char *line, char *last_line)
{
	char *nline;
	char *tmp;
	int i;
	t_hist *hist;

	i = 0;
	hist = g_tracking.mysh->hist;
	// hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	tmp = ft_strrdup(line, i);
	while (hist->previous && hist->index != ft_atoi(tmp))
		hist = hist->previous;
	if ((!hist->previous && hist->index != ft_atoi(tmp))|| i == 0 || i >= 5)
		{
			free(tmp);
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return nline;
}

char	*shebang_num_neg(char *line, char *last_line)
{
	char *nline;
	char *tmp;
	int i;
	t_hist *hist;

	hist = get_hist_nbr(1);
	i = 0;
	// hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			g_tracking.shebang = 1;
			return NULL;
		}
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	tmp = ft_strrdup(line, i);
	while (hist->next)
	{
		if (hist->index != ft_atoi(tmp))
			hist = hist->next;
		else
			break;
	}
	if ((!hist->next && hist->index != ft_atoi(tmp))|| i == 0 || i >= 5)
		{
			free(tmp);
			ft_putendl_fd("Event not found", 2);
			return NULL;
		}
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return nline;
}

char 	*shebang_parse_switch(char *line)
{
	int 	i;
	char	*tmp_line;

	i = 0;
	g_tracking.shebang = 0;
	while (g_tracking.shebang != 1 && line && line[i])
	{
		if (line[i] && line[i] == '!')
		{
			i++;
			tmp_line = ft_strrdup(line, i-1);
			if (ft_iswhitespace(line[i]) || !line[i] || line[i] == ';')
				i++;
			else if (line[i] && line[i] == '!')
			{
				i++;
				line = shebang_last(&line[i], tmp_line);
				i = 0;
			}
			else if (line[i] && line[i] == '-')
			{
				i++;
				if (line[i] && ft_isdigit(line[i]))
					line = shebang_num_neg(&line[i], tmp_line);
				else if (line[i])
					line = shebang_word(&line[i], tmp_line);
				i = 0;
			}
			else if (line[i] && ft_isdigit(line[i]))
			{
				line = shebang_num_pos(&line[i], tmp_line);
				i = 0;
			}
			else if (line[i] && !ft_isdigit(line[i]))
			{
				line = shebang_word(&line[i], tmp_line);
				i = 0;
			}
			free(tmp_line);
		}
		else
			i++;
	}
	line && g_tracking.shebang == 2 ? ft_putendl(line) : NULL;
	return line ;
}