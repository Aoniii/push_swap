/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:59:02 by snourry           #+#    #+#             */
/*   Updated: 2025/05/12 11:59:02 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_BONUS_H
# define PUSHSWAP_BONUS_H

# include "pushswap.h"

typedef struct s_instruction
{
	void	((*f)(t_list **, t_type, bool));
	t_type	type;
	char	*code;
}	t_instruction;

#endif
