/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:03:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/29 19:34:10 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_job					*job_new(char *cmd, t_proc *plist)
{
	t_job				*job;

	if ((job = (t_job *)ft_memalloc(sizeof(t_job))) == NULL)
		return (NULL);
	job->procs = plist;
	job->stdin = STDIN_FILENO;
	job->command = cmd;
	job->stdout = STDOUT_FILENO;
	job->stderr = STDERR_FILENO;
	return (job);
}

void					job_insert(t_job **head, t_job **curr, t_job *j)
{
	if (*head == NULL)
		*head = j;
	else
		(*curr)->next = j;
	*curr = j;
}

void					job_clear(t_job **jobs)
{
	t_job				*j;
	t_job				*tmp;

	j = *jobs;
	*jobs = NULL;
	while (j != NULL)
	{
		proc_clear(&j->procs);
		ft_strdel(&j->command);
		tmp = j;
		j = j->next;
		ft_memdel((void **)&tmp);
	}
}