/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:38:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 18:16:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					prefork_assign(t_ctx *ctx, t_asmt *asmt)
{
	int					pmod;

	pmod = 0;
	while (asmt != NULL)
	{
		pmod |= ft_strcmp(asmt->key, "PATH") == 0;
		astr_env_replace(&ctx->environ, asmt->key, asmt->value);
		asmt = asmt->next;
	}
	if (pmod)
	{
		hash_empty(ctx->hash, &ft_memdel);
		ft_astr_clear(&ctx->path);
		ctx->path = getpath(ctx->environ);
	}
}

int						proc_update_env(t_proc *p)
{
	int					i;
	char				*str;
	int					mod;
	t_asmt				*a;

	mod = 0;
	a = p->asmts;
	while (a != NULL)
	{
		mod |= ft_strcmp("PATH", a->key) == 0;
		str = ft_strjoinc(a->key, a->value, '=');
		if ((i = ft_astr_getkey(p->env, a->key,
								ft_strlen(a->key))) != -1)
		{
			ft_strdel(p->env + i);
			p->env[i] = str;
		}
		else
			ft_astr_append(&p->env, str);
		a = a->next;
	}
	return (mod);
}
