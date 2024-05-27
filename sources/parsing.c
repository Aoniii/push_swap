/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:52:31 by snourry           #+#    #+#             */
/*   Updated: 2024/05/26 21:52:31 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

bool	check(char *s)
{
	int	index;

	index = 0;
	if (!s || !s[0])
		return (0);
	if (s[index] == '-')
		index++;
	while (s[index])
	{
		if (!ft_isdigit(s[index]))
			return (0);
		index++;
	}
	if (s[0] == '-' && index >= 11 && ft_strncmp("-2147483648", s, 12) < 0)
		return (0);
	if (s[0] != '-' && index >= 10 && ft_strncmp("2147483647", s, 11) < 0)
		return (0);
	return (1);
}

bool	duplicate(char **argv)
{
	int	index;

	while (*argv)
	{
		index = 1;
		while (argv[index])
		{
			if (ft_strncmp(*argv, argv[index], 12) == 0)
				return (0);
			index++;
		}
		argv++;
	}
	return (1);
}

t_list	*args(char **argv)
{
	t_list	*list;
	int		*nb;

	list = NULL;
	if (!duplicate(argv))
		return (NULL);
	while (*argv)
	{
		nb = malloc(sizeof(int));
		if (!nb || !check(*argv))
		{
			free(nb);
			nb = NULL;
			ft_lstclear(&list, &free);
			return (NULL);
		}
		*nb = ft_atoi(*argv);
		ft_lstadd_back(&list, ft_lstnew(nb));
		argv++;
	}
	return (list);
}
