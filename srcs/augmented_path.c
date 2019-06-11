/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmented_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:54:12 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 13:58:16 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "room.h"

static void	open_path(t_room **current, t_room **next)
{
	t_room	*room_boundary;
	t_room	*from;

	room_boundary = *current;
	*current = room_boundary->next;
	room_boundary->next = *next;
	room_boundary->from = *next;
	from = room_boundary;
	while (!is_junction(*current))
	{
		(*current)->flag ^= FL_CLOSE_PATH;
		*next = (*current)->next;
		(*current)->next = 0;
		(*current)->from = from;
		from = *current;
		*current = *next;
	}
	room_boundary = *current;
	*current = room_boundary->from_junction;
	room_boundary->from = from;
	*next = room_boundary;
}

void		save_augmented_path(t_env *env)
{
	t_room	*current;
	t_room	*from;
	t_room	*next;

	current = env->end;
	next = 0;
	from = 0;
	while (current->from)
	{
		from = current->from;
		if (!is_closed_path(current))
		{
			if (current != env->end)
				current->flag |= FL_CLOSE_PATH;
			current->next = next;
			current->from = next;
			next = current;
			current = from;
		}
		else
			open_path(&current, &next);
	}
	current->next = next;
	current->from = next;
}

static void	close_path(t_room **current, t_room **from)
{
	t_room	*room_boundary;
	t_room	*next;

	room_boundary = *current;
	*current = room_boundary->from;
	room_boundary->from = *from;
	next = room_boundary;
	while (!is_closed_path(*current))
	{
		(*current)->flag |= FL_CLOSE_PATH;
		*from = (*current)->from;
		(*current)->next = next;
		(*current)->from = next;
		next = *current;
		*current = *from;
	}
	room_boundary = *current;
	*current = room_boundary->next;
	room_boundary->next = next;
	*from = room_boundary;
}

void		reset_to_previous_augmented_path(t_env *env)
{
	t_room	*current;
	t_room	*from;
	t_room	*next;

	current = env->start;
	next = 0;
	from = 0;
	while (current->next)
	{
		next = current->next;
		if (!is_junction(current))
		{
			if (current != env->start)
				current->flag ^= FL_CLOSE_PATH;
			current->next = 0;
			current->from = from;
			from = current;
			current = next;
		}
		else
			close_path(&current, &from);
	}
	current->next = 0;
	current->from = from;
}
