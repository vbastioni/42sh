/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:48:13 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:12:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** function written for tputs to output the characters
*/

int		ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

bool	str_isblank(char *s)
{
	while (*s)
	{
		if (*s != '\t' && *s != ' ')
			return (false);
		s++;
	}
	return (true);
}

bool	dlst_isblank(t_dlist *dlst)
{
	while (dlst)
	{
		if (str_isblank(dlst->data) == false)
			return (false);
		dlst = dlst->next;
	}
	return (true);
}

bool	is_number(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

bool	is_number_w_dash(char *str)
{
		while (*str)
		{
			if (ft_isdigit(*str) == false)
			{
				if (*str == '-' && *(str + 1) == '\0')
					return (true);
				else
					return (false);
			}
			str++;
		}
		return (false);
}
