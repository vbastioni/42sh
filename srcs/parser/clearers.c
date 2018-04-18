/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:49:00 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/18 18:24:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		rdir_clear(t_redir **rdirs)
{
	t_redir *r;

	r = *rdirs;
	while (r)
	{
		r = *rdirs;
		*rdirs = (t_redir *)(*rdirs)->next;
		free(r->s_rhs);
		ft_memdel((void **)&r);
		r = *rdirs;
	}
}

void		proc_clear(t_proc **proc)
{
	t_proc			*p;
	t_proc			*t;

	if (proc == NULL)
		return ;
	p = *proc;
	*proc = NULL;
	while (p != NULL)
	{
		t = p;
		p = p->next;
		if (t->type == BINARY || t->type == EXNFOD)
			ft_strdel(&t->data.path);
		if (t->argv != NULL)
			ft_astr_clear(&t->argv);
		if (t->env != NULL)
			ft_astr_clear(&t->env);
		if (t->asmts != NULL)
			asmt_clear(&t->asmts);
		rdir_clear(&t->redirs);
		ft_memdel((void **)&t);
	}
}

void		asmt_clear(t_asmt **asmt)
{
	t_asmt			*a;
	t_asmt			*t;

	a = *asmt;
	*asmt = NULL;
	while (a != NULL)
	{
		t = a;
		a = a->next;
		ft_strdel(&t->key);
		if (t->value != NULL)
			ft_strdel(&t->value);
		ft_memdel((void **)&t);
	}
}

static void	*job_clear(t_job **job)
{
	t_job				*j;

	j = *job;
	*job = NULL;
	proc_clear(&j->procs);
	ft_memdel((void **)&j);
	return (NULL);
}

void		*job_clearall(t_job **job)
{
	t_job	*j;
	t_job	*t;

	if (job == NULL || *job == NULL)
		return (NULL);
	j = *job;
	*job = NULL;
	while (j != NULL)
	{
		t = j;
		j = j->forward;
		job_safeclear(&t);
	}
	return (NULL);
}

void		*job_safeclear(t_job **job)
{
	t_job	*j;
	t_job	*t;

	if (job == NULL || *job == NULL)
		return (NULL);
	j = *job;
	while (j != NULL)
	{
		t = j;
		j = j->next;
		job_clear(&t);
	}
	return (NULL);
}
