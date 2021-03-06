/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:18:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/21 12:48:42 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int					expand_split(char *str, t_list **lst)
{
	t_list			*l;

	if ((l = bridge_strsplit(str)) == NULL)
		return (-1);
	*lst = l;
	return (1);
}

int					err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (0);
}

static void			lcleanup(int ret, char **tmp, char **swp)
{
	if (ret > 0)
	{
		ft_strdel(tmp);
		*tmp = *swp;
		*swp = NULL;
	}
}

static int			ret_err(char **str, int val)
{
	ft_strdel(str);
	return (val);
}

int					expand(char *str, t_ctx *ctx, t_list **lst)
{
	char			*tmp;
	char			*swp;
	int				ret;

	if (ft_strcmp(str, "") == 0)
		return (0);
	tmp = NULL;
	ret = expand_tilde(str, &tmp, ctx);
	tmp = (ret == 0) ? ft_strdup(str) : tmp;
	ret = expand_braces(tmp, &swp);
	lcleanup(ret, &tmp, &swp);
	if (ret == -1)
		return (ret_err(&tmp, -3));
	ret = expand_param(tmp, &swp, ctx);
	if (ret == -1)
		return (ret_err(&tmp, -3));
	lcleanup(ret, &tmp, &swp);
	if ((ret = expand_split(tmp, lst)) == -1)
		return (ret_err(&tmp, -1));
	ft_strdel(&tmp);
	ret = expand_glob(*lst, ctx);
	if (ret < 1)
		return (ret);
	expand_quotes(*lst);
	return (1);
}
