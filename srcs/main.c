/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 12:30:38 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "parser.h"
#include "error.h"
#include "output.h"
#include "cleaner.h"
#include "path_utils.h"

int			main(void)
{
	static t_env	env;
	int				status;

	status = parser(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	matrix_filter(&env);
//	if ((status = check_map(&env)) != SUCCESS)
//		return (print_error_and_return(status));
	status = solver(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	status = fill_paths_array(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	print_output(&env);
	return (free_mem(&env));
}
