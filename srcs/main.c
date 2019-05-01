/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 13:37:48 by apion            ###   ########.fr       */
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
**	- room coord can be < 0 (subject: "coord are integer")
**	- max_flow <= min(nb_tube_out_start, nb_tube_in_end) //because some in_end may not be linked to start
*/

int			main(void)
{
	static t_env	env;
	int				status;

	status = parser(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	//print_matrix(&env);
	matrix_filter(&env);
	if ((status = check_map(&env)) != SUCCESS)
		return (status);
	print_output(&env);
	return (free_mem(&env));
}
