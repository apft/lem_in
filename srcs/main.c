/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:52:31 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 10:25:05 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"

int		main(void)
{
	static t_env	env;
	int				status;

	status = parser(&env);
	if (status < 0)
		return (status);
	return (0);
}
