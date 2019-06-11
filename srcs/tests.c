/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:48:18 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 18:45:19 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_printf.h"
#include <stdlib.h>

#define ASSERT_TEST(cond, format, args...) \
	do { \
		if (cond) break; \
		ft_dprintf(2, format "\n", ##args); \
		exit (1); \
	} while (0)

static int	compute_path_length(t_room *current)
{
	int             length;

	length = 0;
	while (current)
	{
		current = current->next;
		++length;
	}
	return (length);
}

static int	add_path_length(t_room *start, t_room *current,
				t_env *env, int *flow)
{
	(void)start;
	(void)env;
	if (!is_closed_path(current))
		return (LOOP_CONTINUE);
	*flow += compute_path_length(current);
	return (LOOP_SUCCESS);
}

static int	compute_flow(t_env *env)
{
	int             flow;

	flow = 0;
	apply_foreach_room_linked_to_ref(env->start, env, &flow, &add_path_length);
	return (flow);
}

void		test_flow(t_env *env)
{
	static int	flow_by_cost;
	int			flow_by_length;

	flow_by_cost += external_cost(env->end);
	flow_by_length = compute_flow(env);
	ASSERT_TEST(flow_by_cost == flow_by_length,
			"error: flow_by_cost= %d, flow_by_length= %d, cost_end= %d",
			flow_by_cost, flow_by_length, external_cost(env->end));
}

void		test_cost(t_room *current)
{
	ASSERT_TEST(external_cost(current) >= 0, "error: negative external cost");
	ASSERT_TEST(internal_cost(current) >= 0, "error: negative internal cost");
}
