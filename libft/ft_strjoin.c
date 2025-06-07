/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:37:55 by snourry           #+#    #+#             */
/*   Updated: 2022/03/30 22:37:55 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allows and returns a new string, the result of the concatenation.
 * 
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return (char*) The new string.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1 && s1[++j])
		str[++i] = s1[j];
	j = -1;
	while (s2[++j])
		str[++i] = s2[j];
	str[i + 1] = '\0';
	return (str);
}
