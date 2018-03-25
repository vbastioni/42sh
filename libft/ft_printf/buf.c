/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:36:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/21 12:02:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf				*fpf_buf_get(void)
{
	static t_buf	buf = (t_buf) {.init = 0};

	return (&buf);
}

void				fpf_buf_init(t_buf *buf)
{
	if (buf == NULL)
		buf = fpf_buf_get();
	if (buf->type != FPF_S)
		buf->buf = qbuf_new(1 << 8);
	buf->init = 1;
}

int					fpf_buf_clear(t_buf *buf)
{
	char			*str;

	if (buf == NULL)
		buf = fpf_buf_get();
	if (buf->type == FPF_S)
	{
		buf->init = 0;
		return (1);
	}
	else if (buf->type == FPS_A)
	{
		str = ft_strndup(buf->buf->buffer,
							(size_t)buf->ret > buf->len ? buf->len : buf->ret);
		*(buf->out.out) = str;
	}
	else
		write(buf->out.fd, buf->buf->buffer, buf->buf->used);
	qbuf_del(&buf->buf);
	return (1);
}