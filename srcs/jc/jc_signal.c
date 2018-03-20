/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:37:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 09:12:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				ldojob(t_job *j, t_ctx *ctx, size_t i)
{
	t_job				*next;

	jc_updatepipe(j);
	if (j->status & JOB_CMP)
	{
		next = (j->status & 0xFF) ? j->err : j->ok;
		printf("%s is cmp, done? %d\n", j->parent->command, next == NULL);
		if (next != NULL)
		{
			ctx->bg_jobs[i] = next;
			job_exec(ctx->bg_jobs[i], ctx);
		}
		else
		{
			j->status = (j->status & ~0xFF) | JOB_CMP;
			j->parent->status = j->status | JOB_DON;
		}
	}
}

static void				lhandle_rem(t_ctx *ctx)
{
	pid_t				pid;
	int					status;
	t_proc				*p;
	int					i;

	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) > 0)
	{
		if ((i = jc_jobfind(ctx, pid, &p)) != -1)
			jc_updateproc(ctx->bg_jobs[i], p, status);
	}
}

void					jc_signal(int signo)
{
	t_ctx				*ctx;
	size_t				i;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr();
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			ldojob(ctx->bg_jobs[i], ctx, i);
		i++;
	}
	lhandle_rem(ctx);
}
