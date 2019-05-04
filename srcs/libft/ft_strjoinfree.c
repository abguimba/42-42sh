/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:26:05 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/08 15:44:56 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_it(char **s1, char **s2, size_t free_level)
{
	if (free_level == 1)
	{
		ft_free((char *)(*s1));
		s1 = NULL;
	}
	if (free_level == 2)
	{
		ft_free((char *)(*s2));
		s2 = NULL;
	}
	if (free_level == 3)
	{
		ft_free((char *)(*s1));
		s1 = NULL;
		ft_free((char *)(*s2));
		s2 = NULL;
	}
}

char	*ft_switch(char *s1, char *s2)
{
	if (s1 == NULL && s2)
		return (s2);
	if (s2 == NULL && s1)
		return (s1);
	else
		return (NULL);
}

char	*ft_strjoinfree(char *s1, char *s2, size_t free_level)
{
	size_t	i;
	char	*nstring;
	size_t	size_s1;
	size_t	size_s2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if ((nstring = ft_malloc(sizeof(char) * (size_s1 + size_s2 + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		nstring[i] = s1[i];
		i++;
	}
	while (i < size_s1 + size_s2)
	{
		nstring[i] = s2[i - size_s1];
		i++;
	}
	nstring[i] = '\0';
	free_it(&s1, &s2, free_level);
	return (nstring);
}

char	*ft_strjoinchar(char const *s1, char s2, size_t free_level)
{
	size_t	i;
	char	*nstring;
	size_t	size_s1;

	size_s1 = ft_strlen(s1);
	if (s1 == NULL || s2 == '\0')
		return (NULL);
	if ((nstring = ft_malloc(sizeof(char) * (size_s1 + 2))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		nstring[i] = s1[i];
		i++;
	}
	nstring[i] = s2;
	i++;
	nstring[i] = '\0';
	if (free_level == 1)
		ft_free((char *)(s1));
	return (nstring);
}
