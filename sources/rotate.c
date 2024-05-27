/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rorate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:34:10 by snourry           #+#    #+#             */
/*   Updated: 2024/05/27 13:34:10 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	operator(t_list **list)
{
	t_list	*tmp;

	if (ft_lstsize(*list) < 2)
		return ;
	tmp = *list;
	*list = (*list)->next;
	tmp->next = NULL;
	ft_lstlast(*list)->next = tmp;
}

void	rotate(t_list **list, t_type type)
{
	if (type == A)
	{
		operator(&list[A]);
		ft_putendl_fd("ra", 1);
	}
	else if (type == B)
	{
		operator(&list[B]);
		ft_putendl_fd("rb", 1);
	}
	else if (type == BOTH)
	{
		operator(&list[A]);
		operator(&list[B]);
		ft_putendl_fd("rr", 1);
	}
}
