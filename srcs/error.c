/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:09:34 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 18:18:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlinb.h>
#include "error.h"

static void	custom_print_error(char *error_msg)
{
	ft_dprintf("ERROR");
	if (OPTION_ERROR)
		ft_dprintf(STDERR_FILEN0, ": %s", error_msg);
	ft_dprintf("\n");
}

static char	*custom_strerror(int error)
{
	return ("your error message here");
}

void		print_error(int error)
{
	char	*error_msg;

	if (error > 0)
		error_msg = strerror(error);
	else
		error_msg = custom_strerror(error);
	custom_print_error(error_msg);
}
