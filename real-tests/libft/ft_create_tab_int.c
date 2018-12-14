/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:53:25 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/22 12:19:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**ft_create_tab_int : create an int table, with a stricly positive size
**every paces are filled zith 0
**if option_end param is not zero it allocate one more space, fill with value
*/

int		*ft_create_tab_int(int size, int option_end)
{
	int		*res;
	int		i;

	if (option_end != 0)
		size++;
	if (size <= 0)
		return (NULL);
	if (!(res = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = 0;
		i++;
	}
	if (option_end != 0)
		res[size - 1] = option_end;
	return (res);
}
