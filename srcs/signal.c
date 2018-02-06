/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:04:12 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 19:06:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Définit les comportements pour chaque signal
** SIGINT réaffiche le prompt et kill les process en cours
*/

static void	sighandler(int signum)
{
	t_21sh *env;
	
	env = get_envaddr(NULL);
	if (signum == SIGWINCH && env->line_edition)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws);
		if (env->cur_line)
		{
			update_line(env, env->cur_line);
			clear_line(env, env->cur_line);
			redraw_line(env, env->cur_line);
		}
	}
	else if (signum == SIGINT)
	{
		//
	}
	else if (signum == SIGTSTP)
	{
		//
	}
	// SIGTERM + SIGQUIT
}

int		wrap_signal(void)
{
	if (signal(SIGWINCH, &sighandler) == SIG_ERR) // Window size change
		return (FAILSETSIGHDLR);
	if (signal(SIGTSTP, &sighandler) == SIG_ERR)//C-z
		return (FAILSETSIGHDLR);
	if (signal(SIGINT, &sighandler) == SIG_ERR)// C-c
		return (FAILSETSIGHDLR);
//	if (signal(SIGQUIT, &sighandler) == SIG_ERR) // "C-\"
//		return (FAILSETSIGHDLR);
	if (signal(SIGTERM, &sighandler) == SIG_ERR) // "kill command"
		return (FAILSETSIGHDLR);
	return (SUCCESS);
}
