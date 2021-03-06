/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_explorer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:47:17 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 15:58:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_EXPLORER_H
# define DIR_EXPLORER_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>

# include "pattern_matching.h"

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct s_mtok	t_mtok;

typedef struct s_ctx	t_ctx;

typedef struct s_entry	t_entry;

struct					s_entry
{
	char				*name;
	char				*path;
	t_entry				*next;
};

int						expand_glob(t_list *lst, t_ctx *ctx);
int						do_expand_glob(char **str);

t_entry					*ent_create(char *path, char *name);
void					ent_clear(t_entry **ent);
void					ent_free(t_entry **ent);

void					ent_insert(t_entry **head, t_entry **curr,
									t_entry *tmp);
t_entry					*ent_last(t_entry *e);

t_entry					*ent_matching(t_mtok *tok, t_entry *dat);
t_entry					*ent_dirs(t_entry *dat);
int						ent_addslash(t_entry *dats);
void					ent_print(t_entry *ent, int lfmt);
char					*ent_cat(t_entry *entries, int append);
int						ent_match(char *str, t_mtok *tokens);
int						handle_matched(t_mtok *tok, t_entry **matched,
										t_entry *dats);

int						dir_explore(char *path, t_entry **ret, int show_hidden);

t_list					*bridge_strsplit(char *str);

#endif
