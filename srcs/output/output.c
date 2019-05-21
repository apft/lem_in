/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:06:53 by apion             #+#    #+#             */
/*   Updated: 2019/05/21 16:23:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "ft_printf.h"
#include "output.h"

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
	while (i < env->nb_room)
	{
		if (env->matrix[env->start->id][i] && (env->rooms_array[i]->flag & FL_CLOSE_PATH))
			print_path(env, env->rooms_array[i]);
		++i;
	}
}

void		print_output(t_env *env)
{
	print_lines(env->lines);
	ft_putchar('\n');
	//print_matrix(env);
	ft_printf("length of shortest path start->end: %d\n", env->end->dst_min_to_start);
	ft_printf("\nPaths:\n");
	print_paths(env);
}
