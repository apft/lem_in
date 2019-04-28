/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:59:38 by apion             #+#    #+#             */
/*   Updated: 2019/04/28 16:25:20 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_printf.h"
#include "libft.h"

static void	print_header_line(t_room **rooms_array, int size, int width)
{
	int		i;

	i = 0;
	ft_printf(" %*s ╭%{u}", width, "");
	while (i < size)
	{
		ft_printf(" %*s ", width, rooms_array[i]->name);
		++i;
	}
	ft_printf("%{/u}\n");
}

static void	print_rows(t_env *env, int width)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->nb_room)
	{
		if (ft_strequ(env->rooms_array[i]->name, env->start->name))
			ft_printf(">%*s |", width, env->rooms_array[i]->name);
		else if (ft_strequ(env->rooms_array[i]->name, env->end->name))
			ft_printf(" %*s*|", width, env->rooms_array[i]->name);
		else
			ft_printf(" %*s |", width, env->rooms_array[i]->name);
		j = 0;
		while (j < env->nb_room)
		{
			ft_printf(" %*d ", width, env->matrix[i][j]);
			++j;
		}
		ft_putchar('\n');
		++i;
	}
}

static int	get_width_room_max(t_room **rooms, size_t size)
{
	int		max;
	int		len;

	max = 0;
	while (size--)
	{
		len = ft_strlen(rooms[size]->name);
		if (len > max)
			max = len;
	}
	return (max);
}

static void	print_and_return(char *msg)
{
	ft_printf("%s", msg);
	return ;
}

void		print_matrix(t_env *env)
{
	int		width_room_max;

	if (!env->nb_room)
		return (print_and_return("empty room\n"));
	if (!env->matrix)
		return (print_and_return("empty matrix\n"));
	if (!env->rooms_array)
		return (print_and_return("empty rooms array\n"));
	width_room_max = get_width_room_max(env->rooms_array, env->nb_room);
	print_header_line(env->rooms_array, env->nb_room, width_room_max);
	print_rows(env, width_room_max);
}
