/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 15:20:06 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "options.h"
#include "parser.h"
#include "error.h"
#include "map.h"
#include "solver.h"
#include "output.h"
#include "cleaner.h"
#include "path_utils.h"
#include <stdlib.h>

int			main(int ac, char **av)
{
	static t_env	env;
	int				status;

	status = get_options(ac, av, &env);
	if (status != SUCCESS)
		return (print_error_and_return(status, &env));
	status = parser(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status, &env));
	matrix_filter(&env);
//	if ((status = check_map(&env)) != SUCCESS)
//		return (print_error_and_return(status));
	status = solver(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status, &env));
	status = fill_paths_array(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status, &env));
	print_output(&env);
	return (free_mem(&env));
}
