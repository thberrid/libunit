/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:44:43 by jmartel           #+#    #+#             */
/*   Updated: 2018/11/22 12:44:47 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int x, int y)
{
	if (y < 0)
		return (0);
	if (y == 0)
		return (1);
	return (x * ft_pow(x, y - 1));
}
