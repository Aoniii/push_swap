/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:52:33 by snourry           #+#    #+#             */
/*   Updated: 2025/05/13 11:52:33 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_stack	*stack_new(void *content)
{
	t_stack	*list;

	list = malloc(sizeof(t_stack));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = 0;
	return (list);
}
