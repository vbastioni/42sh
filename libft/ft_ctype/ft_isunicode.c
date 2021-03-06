/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isunicode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:31:28 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 15:01:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"

int		ft_isunicode(wchar_t a)
{
	if (a >= 0xD800 && a <= 0xDFFF)
		return (-1);
	else if (a > 0x10FFFF)
		return (-1);
	else if (a < 0x0)
		return (-1);
	else if (MB_CUR_MAX == 1 && a > 0xFF)
		return (-1);
	else
		return (0);
}
