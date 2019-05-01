/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 11:11:21 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "parser.h"
#include "error.h"
#include "output.h"
#include "cleaner.h"

/*
** Discussion:
**	- start == end
**	- invalid number of args in room (not detected -> goes into room name)
*/

void		dijkstra(t_env *env);
int			main(void)
{
	static t_env	env;
	int				status;

	status = parser(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	print_matrix(&env);
	matrix_filter(&env);
	if ((status = check_map(&env)) != SUCCESS)
		return (status);
	print_output(&env);
	return (free_mem(&env));
}
