/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/13 11:24:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					ft_fg(t_proc *p, t_ctx *ctx)
{
	size_t			i;
	t_job			*j;
	char			*str;

	p->type = BU_STR;
	j = NULL;
	if (p->argv[1] == NULL)
		j = (ctx->bgs == NULL) ? NULL : (t_job *)ctx->bgs->content;
	else
		j = jc_jobspec(p, ctx);
	if (j != NULL)
	{
		i = jc_findid(ctx, j);
		jc_restore(j);
		job_putfg(j, ctx);
	}
	else
	{
		asprintf(&str, BU_JOB_ERR, "fg", BU_JOB_NO);
		p->data.str = str;
	}
	return (0);
}
