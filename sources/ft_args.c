/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 02:09:06 by snourry           #+#    #+#             */
/*   Updated: 2022/04/30 02:09:06 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pushswap.h"

static int	ft_check(char *s)
{
	int	index;

	index = -1;
	if (!s[0])
		return (FALSE);
	while (s[++index])
		if (s[index] != ' ' && !ft_isdigit(s[index]))
			if (!(s[index + 1] && s[index] == '-' && ft_isdigit(s[index + 1])))
				return (FALSE);
	return (TRUE);
}

static char	*ft_spejoin(char *s1, char *s2)
{
	char	*final;
	int		i;

	final = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!final)
		return (NULL);
	i = -1;
	while (s1[++i])
		final[i] = s1[i];
	final[i++] = ' ';
	while (*s2)
		final[i++] = *s2++;
	final[i] = '\0';
	free(s1);
	s1 = NULL;
	return (final);
}

static char	*ft_alljoin(int word, char **arg)
{
	char	*string;
	int		index;

	index = 1;
	string = ft_strdup(arg[0]);
	while (--word > 1)
		string = ft_spejoin(string, arg[index++]);
	return (string);
}

static t_stack	*ft_tostack(char *string)
{
	char	**tab;
	t_stack	*stack;
	int		index;

	tab = ft_split(string, ' ');
	index = 0;
	stack = NULL;
	while (tab[index])
	{
		stack = ft_newstack(stack, NULL, ft_atoll(tab[index]));
		if (stack->prev)
			stack->prev->next = stack;
		free(tab[index]);
		tab[index] = NULL;
		index++;
	}
	free(tab);
	tab = NULL;
	stack = ft_firststack(stack);
	return (stack);
}

t_stack	*ft_get_args(int argc, char **argv)
{
	t_stack	*stack;
	char	*string;
	int		index;

	index = -1;
	while (argv[++index])
		if (!ft_check(argv[index]))
			return (NULL);
	stack = NULL;
	if (argv[1])
		string = ft_alljoin(argc, argv);
	else
		string = ft_strdup(argv[0]);
	stack = ft_tostack(string);
	free(string);
	string = NULL;
	return (stack);
}
