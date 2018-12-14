/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:24:53 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/12 16:24:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_last(t_list *start, t_list *new)
{
	if (!start || !new)
		return ;
	while (start->next != NULL)
		start = start->next;
	start->next = new;
	new->next = NULL;
	return ;
}
