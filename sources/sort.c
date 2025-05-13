/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:24:29 by snourry           #+#    #+#             */
/*   Updated: 2024/05/28 18:24:29 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sort_three(t_container **container)
{
	if (*((int *)(container[A]->head->content)) > \
	*((int *)(container[A]->head->next->content)))
		swap(container, A, 1);
	if (*((int *)(container[A]->tail->content)) != \
	get_max_value(container[A]->head))
		reverse_rotate(container, A, 1);
	if (*((int *)(container[A]->head->content)) > \
	*((int *)(container[A]->head->next->content)))
		swap(container, A, 1);
}

static void	sort_four(t_container **container)
{
	while (*((int *)(container[A]->head->content)) != \
	get_min_value(container[A]->head))
		rotate(container, A, 1);
	push(container, B, 1);
	sort_three(container);
	push(container, A, 1);
}

void	sort_five(t_container **container)
{
	int	min;

	min = identify_bottom(container[A]->head, 2);
	while (*((int *)(container[A]->head->content)) > min)
		rotate(container, A, 1);
	push(container, B, 1);
	sort_four(container);
	push(container, A, 1);
	if (*((int *)(container[A]->head->content)) > \
	*((int *)(container[A]->head->next->content)))
		swap(container, A, 1);
}

void	sort(t_container **container)
{
	int	size;

	if (is_sorted(container))
		return ;
	size = container[A]->size;
	if (size < 2)
		return ;
	else if (size == 2)
		swap(container, A, 1);
	else if (size == 3)
		sort_three(container);
	else if (size == 4)
		sort_four(container);
	else if (size == 5)
		sort_five(container);
	else
		sort_big(container);
}
