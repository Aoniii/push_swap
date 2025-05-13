/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:51:25 by snourry           #+#    #+#             */
/*   Updated: 2025/05/13 11:51:25 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	stack_clear(t_stack **lst, void (*del) (void*))
{
	t_stack	*l;

	if (*lst)
	{
		while (*lst)
		{
			l = (*lst)->next;
			stack_delone(*lst, del);
			*lst = l;
		}
		*lst = 0;
	}
}
