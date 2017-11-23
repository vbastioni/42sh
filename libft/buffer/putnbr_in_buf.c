/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_in_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:07:21 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 15:01:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr_in_buf(int n, char *buf, size_t *i)
{
	char *s;

	s = ft_itoa(n);
	puts_in_buf(s, buf, i);
}
