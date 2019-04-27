/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 22:16:02 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "parser.h"
#include "error.h"
#include "output.h"

static int	free_mem(t_env *env)
{
	// TODO: free all memory
	free((void **)env->rooms_array);
	return (SUCCESS);
}

int		main(void)
{
	static t_env	env;
	int				status;

	status = parser(&env);
	if (status != SUCCESS)
		return (free_mem(&env) + print_error_and_return(status));
	print_output(&env);
	return (free_mem(&env));
}
