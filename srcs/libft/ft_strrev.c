/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:06:21 by bsiche            #+#    #+#             */
/*   Updated: 2018/05/23 20:15:53 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char const *s1, int freeit)
{
	size_t	i;
	char	*nstring;

	nstring = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (nstring == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		nstring[ft_strlen(s1) - i - 1] = s1[i];
		i++;
	}
	nstring[i] = '\0';
	if (freeit == 1)
		free((char*)s1);
	return (nstring);
}
