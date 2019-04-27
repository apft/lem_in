/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:06:53 by apion             #+#    #+#             */
/*   Updated: 2019/04/27 18:13:03 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

static void	print_room_names(t_env *env)
{
	t_list	*map;

	map = env->map;
	while (map)
	{
		ft_putendl(((t_room *)map->content)->name);
		map = map->next;
	}
}

void		print_output(t_env *env)
{
	print_lines(env->lines);
	ft_putchar('\n');
	print_room_names(env);
}
