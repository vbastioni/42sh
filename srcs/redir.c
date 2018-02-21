/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:07:55 by lportay           #+#    #+#             */
/*   Updated: 2018/02/21 16:59:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


//vérifier si on peut accéder au fichier pour la redirection

int		get_right_op(t_redir *tok)
{
	if (is_number(tok->s_rhs) == true)
		tok->fd_rhs = ft_atoi(tok->s_rhs);
	else if (*tok->s_rhs == '-' && ft_strlen(tok->s_rhs) == 1)
		tok->dash = true;
	else if (is_number_w_dash(tok->s_rhs) == true)
	{
		tok->fd_rhs = ft_atoi(tok->s_rhs);
		tok->dash = true;
	}
	else
		return (-1);
	return (0);
}

int		r_great_dgreat(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & GREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
	{
		perror(r->s_rhs);
		return (-1);
	}
	if (dup2(tmp, r->lhs) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_less(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_RDONLY)) == -1)
	{
		perror(r->s_rhs);
		return (tmp);
	}
	if (dup2(tmp, r->lhs) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_tless(t_redir *r)
{
	int		fd;

	if ((fd = ft_tmpfile()) == -1)
		return (-1);
	if (write(fd, r->s_rhs, ft_strlen(r->s_rhs)) == -1)
		return (-1);
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (-1);
	if (dup2(fd, r->lhs) == -1)
		return (-1);
	close(fd);
	return (0);
}

int		r_dless(t_heredoc *r)
{
	t_ctx	*ctx;

	ctx = get_ctxaddr(NULL);
	ctx->heredoc_eof = r->s_rhs;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->tios);
	wrap_lineread(ctx, &r->hdoc, PS2);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->oldtios);
	ctx->heredoc_eof = NULL;
	free(r->s_rhs);
	if (r->hdoc.split_line && r->hdoc.split_line->next)
		r->s_rhs = dlst_to_str(r->hdoc.split_line);
	else
		r->s_rhs = ft_strdup("");
	r_tless((t_redir *)r);

	if (r->hdoc.split_line)
		ft_dlstdel(&r->hdoc.split_line, &delvoid);
	if (r->hdoc.yank)
		ft_dlstdel(&r->hdoc.yank, &delvoid);
	if (r->hdoc.linestate)
		stack_del(&r->hdoc.linestate);

	return (0);
}

int		r_andgreat_anddgreat(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & ANDGREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
	{
		perror(r->s_rhs);
		return (tmp);
	}
	if (dup2(tmp, STDOUT_FILENO) == -1)
		return (-1);
	if (dup2(tmp, STDERR_FILENO) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_greatand_lessand(t_redir *r)
{
	if (get_right_op(r) == -1)
	{
		ft_putstr_fd(AMBIG_REDIR,STDERR_FILENO);
		return (-1);
	}
	if (r->fd_rhs != -1)
		if (dup2(r->fd_rhs, r->lhs) == -1)
			return (-1);
	if (r->dash == true && r->fd_rhs != -1)
		close(r->fd_rhs);
	else if (r->dash == true)
		close(r->lhs);
	return (0);
}

int		do_redir(t_redir *r)
{
	int ret;

	while (r)
	{
		if (r->type & (GREAT | DGREAT))
			ret = r_great_dgreat(r);
		else if (r->type & LESS)
			ret = r_less(r);
		else if (r->type & DLESS)
			ret = r_dless((t_heredoc *)r);
		else if (r->type & TLESS)
			ret = r_tless(r);
		else if (IS_AND_REDIR(r->type))
			ret = r_andgreat_anddgreat(r);
		else if (r->type & (GREATAND | LESSAND))
			ret = r_greatand_lessand(r);
		else
			return (-1);
		if (ret == -1)
			return (ret);
		r = (t_redir *)r->next;
	}
	return (0);
}
