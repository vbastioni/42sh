/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:53:15 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 12:02:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLST_H
# define FT_DLST_H

# include <stdlib.h>

/*
** Every list created with this set of functions should have a 'HEAD' maillon
*/

typedef struct		s_dlist
{
	void			*data;
	size_t			content_size;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

t_dlist				*ft_dlstnew(void const *content, size_t content_size);
t_dlist				*ft_dlstnewaddr(void const *content, size_t content_size);
void				ft_dlstadd(t_dlist **alst, t_dlist *new);
void				ft_dlstaddend(t_dlist *alst, t_dlist *new);
void				ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstremove(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlsthead(t_dlist **dlst);
void				ft_dlstend(t_dlist **dlst);
size_t				ft_dlstcount(t_dlist *dlst);
size_t				ft_dlstindex(t_dlist *dlst);
t_dlist				*ft_dlstaddr(t_dlist *dlst, size_t rank);
void				ft_dlstprint(t_dlist *list, char *sep, void (*p)(void *));
void				ft_dlstinsert(t_dlist *previous, t_dlist *between);
t_dlist				*dlst_from_str(char *str);
char				*str_from_dlst(t_dlist *dlst);
t_dlist				*ft_dlstdup(t_dlist *dlst);
int					move_dlst_head(t_dlist **dlist, int movement);
t_dlist				*ft_dlstlast(t_dlist *dlst);
t_dlist				*ft_dlstfirst(t_dlist *dlst);
void				delvoid(void *as, size_t len);
int					ft_dlstnewadd(t_dlist **lst, void *data, size_t sz,
									t_dlist *(*new)(void const *, size_t));
int					ft_dlstnewaddend(t_dlist *lst, void *data, size_t sz,
										t_dlist *(*new)(void const *, size_t));

#endif
