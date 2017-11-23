/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnc_in_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:08:29 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 14:28:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnc_in_buf(int j, char a, char *buf, size_t *i)
{
	while (j-- > 0)
		putc_in_buf(a, buf, i);
}
