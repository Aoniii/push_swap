/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:50:52 by snourry           #+#    #+#             */
/*   Updated: 2025/05/13 11:50:52 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	stack_delone(t_stack *lst, void (*del) (void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
