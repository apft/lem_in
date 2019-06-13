/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:06:53 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 16:22:56 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "env.h"
#include "path.h"
#include "print_ants.h"
#include "options.h"
#include "ft_printf.h"

static void	print_path(t_env *env, t_room *start)
{
	ft_printf("%s\t", env->start->name);
	while (start != env->end)
	{
		ft_printf("%s\t", start->name);
		start = start->next;
	}
	ft_printf("%s\n", env->end->name);
}

void		print_paths(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (env->matrix[env->start->id][i]
				&& (env->rooms_array[i]->flag & FL_CLOSE_PATH))
			print_path(env, env->rooms_array[i]);
		++i;
	}
}

static void	print_paths_array(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_paths)
	{
		ft_printf("%d: (%d, %s, %d)", i, env->paths_array[i]->length,
				env->paths_array[i]->back->name,
				env->paths_array[i]->nb_ants_stream);
		if (i < env->nb_paths - 1)
			ft_printf(" | ");
		i++;
	}
	ft_putchar('\n');
}

static void	print_ants_move_start_end(t_env *env)
{
	int		i;

	i = 1;
	while (i <= env->nb_ants)
	{
		ft_printf("L%d-%s", i, env->end->name);
		if (i < env->nb_ants)
			ft_putchar(' ');
		++i;
	}
	ft_putchar('\n');
}

void		print_output(t_env *env)
{
	print_lines(env->lines);
	ft_putchar('\n');
	if (env->start->flag & FL_DIRECT_TO_END)
		print_ants_move_start_end(env);
	else
	{
		print_all_lines_of_ants_moves(env);
		if (env->options & OP_DEBUG)
		{
			ft_printf("\nNb of ants: %d\n", env->nb_ants);
			ft_printf("\nPaths found:\n");
			print_paths(env);
			ft_printf("\nPaths ordered:\n");
			print_paths_array(env);
		}
	}
}
